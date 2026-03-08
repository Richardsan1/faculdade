from client import client
from threading import Thread

thr_control = []

for i in range(0, 10):
    thr = Thread(target=client, args=["BOT", f"user-{i}"])
    thr.start()
    thr_control.append(thr)

for thr in thr_control:
    thr.join()
