import threading
import socket

HOST = '127.0.0.1'
PORT = 12346
MAX_PAYLOAD = 2048
MIN_LISTEN_CLIENTS = 5 

lock = threading.Lock()
tickets = 10

def buyTicket():
    with lock: 
        global tickets
        if tickets > 0:
            tickets -= 1
            return True
        return False

def main():
    global tickets
    sock = socket.socket(socket.AF_INET,  socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((HOST, PORT))
    try: 
        max_connections = int(input("Set a max connection pool: "))
        tickets_available = int(input("Set how many tickets are available: "))
        if tickets_available > 0:
            tickets = tickets_available
        if max_connections < MIN_LISTEN_CLIENTS:
            max_connections = MIN_LISTEN_CLIENTS
    except ValueError:
        max_connections = MIN_LISTEN_CLIENTS
        print("Error: Values are not accepted, using default values")

    sock.listen(max_connections)
    print(f"Server listening on {HOST}:{PORT}")

    while True: 
        client, address = sock.accept()
        print(f"Connected Client: {address}")
        while True:
            try:
                data = client.recv(MAX_PAYLOAD).decode("utf-8")
                if not data:
                    break
                req = data.upper().strip()
                print (f"Receive: {req}")
                if req == "CONSULTAR":
                    client.send(f"Estoque atual: {tickets}".encode())
                elif req == "COMPRAR":
                    status = buyTicket()
                    if status:
                        client.send(f"Compra realizada. Estoque restante: {tickets}".encode())
                    else:
                        client.send("ERRO: Produto esgotado".encode())
                else:
                    client.send("ERRO: Comando inválido".encode())
            except ConnectionResetError:
                break
        client.close()
        print(f"Cliente desconectado: {address}")

main()