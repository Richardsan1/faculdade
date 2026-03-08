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
            while True:
                vl = random.randint(10, 20)
                msg = ""
                if vl < 14:
                    msg = "CONSULTAR"
                    interactions += 1
                elif vl < 18:
                    msg = "COMPRAR"
                    interactions += 1
                elif vl < 20:
                    msg = "SAIR"
                
                if msg.strip().upper() == "SAIR":
                    if interactions > 10:
                        client_socket.close()
                        log(user, "Desconectado do servidor")
                        break
                    else: 
                        continue
                client_socket.send(msg.encode("utf-8"))
                res = client_socket.recv(2048).decode("utf-8")
                
                log(user, f"ENVIADO: {msg}")
                log(user, F"{dt.now().strftime("%d-%m-%Y %H:%M:%S")} {res  }")
                time.sleep(vl)