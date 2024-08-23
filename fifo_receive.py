FIFO = "./fifo_test"

print("start receiving")
with open(FIFO, 'r') as f:
    while True:
        data = f.readline()
        if data == '':
            break
        print(f"received : {data!r}")
    print("receiving done")
