FIFO_FILENAME = "./fifo_test"

f = open(FIFO_FILENAME, 'w')
for i in range(10):
	f.write(f"Hello, fifo test {i}\n")
	f.flush()
print("sending done")
