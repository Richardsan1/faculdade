import socket
import os
from pathlib import Path
import time
import random

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
        except:
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
                    break
                client_socket.send(msg.encode())
                res = client_socket.recv(2048).decode("utf-8")
                print(res)
        else:
            while True:
                vl = random.randint(1, 10)
                if vl < 4:
                    msg = "CONSULTAR"
                elif vl < 8:
                    msg = "COMPRAR"
                elif vl < 10:
                    msg = "SAIR"
                
                if msg.strip().upper() == "SAIR":
                    client_socket.close()
                    break
                client_socket.send(msg.encode())
                res = client_socket.recv(2048).decode("utf-8")
                
                log(user, msg)
                time.sleep(vl)