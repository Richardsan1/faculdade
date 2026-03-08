from client import client
from threading import Thread

thr_control = []
STRESS_SIZE = 10

for i in range(0, STRESS_SIZE):
    thr = Thread(target=client, args=["BOT", f"user-{i+1}"])
    thr.start()
    thr_control.append(thr)

for thr in thr_control:
    thr.join()
