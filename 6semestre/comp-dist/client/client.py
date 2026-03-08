import socket
import os
from pathlib import Path
import time
import random
from datetime import datetime as dt

HOST = '127.0.0.1'  
PORT = 12346        
def log(user, message):
    pt = Path(f"{os.getcwd()}/logs/")
    if not pt.exists():
        os.mkdir(pt)
    
    with open(f"{pt}/{user}.log", "a") as file:
        file.write(message+ "\n")
        file.close()

def client(mode, user):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            client_socket.connect((HOST, PORT))
            if mode == "BOT":
                log(user, f"Conectado a {HOST}:{PORT}")
            else:
                print(f"Conectado a {HOST}:{PORT}")
        except Exception:
            if mode == "BOT":
                log(user, f"ERRO: Não foi possível se conectar ao host {HOST}")   
            else: 
                print(f"ERRO: Não foi possível se conectar ao host {HOST}")
            return
        if mode == "USER":
            while True:
                msg = input("Digite sua mensagem: ")
                if msg.strip().upper() == "SAIR":
                    client_socket.close()
                    if mode == "BOT":
                        log(user, "Desconectado do servidor")
                    break
                client_socket.send(msg.encode("utf-8"))
                res = client_socket.recv(2048).decode("utf-8")
                print(res)
        else:
            interactions = 0
            while interactions < 10:
                rd1 = random.randint(1, 10)
                msg = "CONSULTAR"
                client_socket.send(msg.encode("utf-8"))
                res = client_socket.recv(2048).decode("utf-8")
                
                log(user, f"ENVIADO: {msg}")
                log(user, F"{dt.now().strftime("%d-%m-%Y %H:%M:%S")} {res  }")
                time.sleep(rd1)
                
                rd2 = random.randint(1, 10)
                msg = "COMPRAR"
                client_socket.send(msg.encode("utf-8"))
                res = client_socket.recv(2048).decode("utf-8")
                
                log(user, f"ENVIADO: {msg}")
                log(user, F"{dt.now().strftime("%d-%m-%Y %H:%M:%S")} {res  }")
                time.sleep(rd2)
                
                interactions +=1

            client_socket.close()
            log(user, "Desconectado do servidor")
