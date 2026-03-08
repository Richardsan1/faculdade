import threading
import socket
import sys

HOST = '127.0.0.1'
PORT = 12346
MAX_PAYLOAD = 2048

class TicketServer:
    MIN_BACKLOG = 5

    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.host, self.port))

        self.tickets = 10
        self.tickets_lock = threading.Lock()

        self.client_count = 0
        self.client_count_lock = threading.Lock()

    def set_parameters(self) -> int:
        try:
            max_connections = int(input("Set a max connection pool: "))
            tickets_available = int(input("Set how many tickets are available: "))

            if max_connections < self.MIN_BACKLOG:
                print(f"Max connections too low, using {self.MIN_BACKLOG}")
                max_connections = self.MIN_BACKLOG

            if tickets_available > 0:
                self.tickets = tickets_available
            else:
                print("Number of tickets must be positive. Using default 10.")

            return max_connections
        except ValueError:
            print("Error: Values are not accepted, using default values")
            return self.MIN_BACKLOG

    def buy_ticket(self) -> bool:
        with self.tickets_lock:
            if self.tickets > 0:
                self.tickets -= 1
                return True
            return False

    def client_connected(self, address):
        with self.client_count_lock:
            self.client_count += 1
            print(f"Client connected: {address}; active connections: {self.client_count}")

    def client_disconnected(self, address):
        with self.client_count_lock:
            self.client_count -= 1
            print(f"Client disconnected: {address}; active connections: {self.client_count}")

    def handle_client(self, client, address):
        self.client_connected(address)
        try:
            while True:
                data = client.recv(MAX_PAYLOAD)
                if not data:
                    break
                req = data.decode("utf-8").upper().strip()
                print(f"Received: {req} from {address}")

                if req == "CONSULTAR":
                    client.send(f"Estoque atual: {self.tickets}".encode("utf-8"))
                elif req == "COMPRAR":
                    status = self.buy_ticket()
                    if status:
                        client.send(f"Compra realizada. Estoque restante: {self.tickets}".encode("utf-8"))
                    else:
                        client.send("ERRO: Produto esgotado".encode("utf-8"))
                else:
                    client.send("ERRO: Comando inválido".encode("utf-8"))
        except ConnectionResetError:
            pass
        finally:
            client.close()
            self.client_disconnected(address)

    def run(self):
        backlog = self.set_parameters()
        self.sock.listen(backlog)
        print(f"Server listening on {self.host}:{self.port}")
        try:
            while True:
                client, address = self.sock.accept()
                print(f"Accepted connection from {address}")
                threading.Thread(
                    target=self.handle_client,
                    args=(client, address),
                    daemon=True,
                ).start()
        except KeyboardInterrupt:
            print("Shutting down server...")
        finally:
            self.sock.close()


def main():
    server = TicketServer(HOST, PORT)
    server.run()


if __name__ == "__main__":
    main()