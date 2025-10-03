import socket
import threading
import sys

TCP_IP = '127.0.0.1'
TCP_PORTA = 10420
TAMANHO_BUFFER = 1024

running = True

def receber_mensagens(cliente_socket):
    global running
    while running:
        try:
            data = cliente_socket.recv(TAMANHO_BUFFER)
            if data:
                mensagem = data.decode('UTF-8')
                print(f"\nServidor: {mensagem}")
                print("Cliente > ", end="", flush=True)
            else:
                print("\nConexão encerrada pelo servidor.")
                running = False
                break
        except socket.error as e:
            print(f"\nErro ao receber mensagem: {e}")
            running = False
            break

def enviar_mensagens(cliente_socket):
    global running
    while running:
        try:
            msg = input("Cliente > ")
            
            if msg.upper() == "QUIT" or msg.upper() == "SAIR":
                running = False
                cliente_socket.send(msg.encode('UTF-8'))
                break
            
            cliente_socket.send(msg.encode('UTF-8'))
            
        except KeyboardInterrupt:
            print("\nEncerrando cliente...")
            running = False
            break
        except socket.error as e:
            print(f"\nErro ao enviar mensagem: {e}")
            running = False
            break

def main():
    global running
    
    try:
        cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        print(f"Conectando ao servidor {TCP_IP}:{TCP_PORTA}...")
        
        cliente.connect((TCP_IP, TCP_PORTA))
        print("Conectado com sucesso!")
        print("Digite 'QUIT' ou 'SAIR' para encerrar a conexão.")
        print("-" * 50)
        
        thread_receber = threading.Thread(target=receber_mensagens, args=(cliente,))
        thread_receber.daemon = True
        thread_receber.start()
        
        enviar_mensagens(cliente)
        
    except ConnectionRefusedError:
        print(f"Erro: Não foi possível conectar ao servidor {TCP_IP}:{TCP_PORTA}")
        print("Verifique se o servidor está rodando.")
    except socket.error as e:
        print(f"Erro de socket: {e}")
    except KeyboardInterrupt:
        print("\nEncerrando cliente...")
    finally:
        running = False
        try:
            cliente.close()
            print("Conexão encerrada.")
        except:
            pass

if __name__ == "__main__":
    main()