import socket

HOST = '127.0.0.1'  
PORT = 12346        

def client():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            client_socket.connect((HOST, PORT))
            print(f"Conectado a {HOST}:{PORT}")
        except:
            print(f"ERRO: Não foi possível se conectar ao host {HOST}")
            return
        
        while True:
            msg = input("Digite sua mensagem: ")
            if msg.strip().upper() == "SAIR":
                client_socket.close()
                break
            client_socket.send(msg.encode())
            res = client_socket.recv(2048).decode("utf-8")
            print(res)

client()