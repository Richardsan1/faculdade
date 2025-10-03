import socket
import threading
import sys

TCP_IP = '127.0.0.1'
TCP_PORTA = 10420
TAMANHO_BUFFER = 1024

running = True

def receber_mensagens(conn):
    global running
    while running:
        try:
            data = conn.recv(TAMANHO_BUFFER)
            if data:
                mensagem = data.decode('UTF-8')
                print(f"\nCliente: {mensagem}")
                print("Servidor > ", end="", flush=True)
                
                if mensagem.upper() == "QUIT" or mensagem.upper() == "SAIR":
                    print("\nCliente desconectou.")
                    running = False
                    break
            else:
                print("\nCliente desconectou.")
                running = False
                break
        except socket.error as e:
            print(f"\nErro ao receber mensagem: {e}")
            running = False
            break

def enviar_mensagens(conn):
    global running
    while running:
        try:
            msg = input("Servidor > ")
            
            if msg.upper() == "QUIT" or msg.upper() == "SAIR":
                running = False
                conn.send(msg.encode('UTF-8'))
                break
            
            conn.send(msg.encode('UTF-8'))
            
        except KeyboardInterrupt:
            print("\nEncerrando servidor...")
            running = False
            break
        except socket.error as e:
            print(f"\nErro ao enviar mensagem: {e}")
            running = False
            break

def handle_client(conn, addr):
    global running
    
    print(f"Cliente conectado: {addr}")
    print("Digite 'QUIT' ou 'SAIR' para encerrar a conexão.")
    print("-" * 50)
    
    try:
        thread_receber = threading.Thread(target=receber_mensagens, args=(conn,))
        thread_receber.daemon = True
        thread_receber.start()
        
        enviar_mensagens(conn)
        
    except Exception as e:
        print(f"Erro ao lidar com cliente: {e}")
    finally:
        conn.close()
        print(f"Conexão com {addr} encerrada.")

def main():
    global running
    
    try:
        servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        servidor.bind((TCP_IP, TCP_PORTA))
        servidor.listen(1)
        
        print(f"Servidor disponível na porta {TCP_PORTA} e escutando...")
        
        while running:
            try:
                conn, addr = servidor.accept()
                handle_client(conn, addr)
                
            except KeyboardInterrupt:
                print("\nEncerrando servidor...")
                running = False
                break
            except socket.error as e:
                print(f"Erro de socket: {e}")
                break
                
    except Exception as e:
        print(f"Erro ao iniciar servidor: {e}")
    finally:
        try:
            servidor.close()
            print("Servidor encerrado.")
        except:
            pass

if __name__ == "__main__":
    main()