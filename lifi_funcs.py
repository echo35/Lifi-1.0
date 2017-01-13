import serial
def timer():
	ser.reset_input_buffer()
	while ser.in_waiting == 0:
		None
	start_time = time.time()
	while True:
		c = ser.read(1)
		if c == "":
			break
	print (time.time()-start_time-ser.timeout)*1000, "milliseconds"

def record(delay):
	ser.reset_input_buffer()
	while ser.in_waiting == 0:
		None
	end_time = time.time()
	count = 1
	while time.time() <= end_time + delay:
		ser.read(1)
		count+=1
	return count

def count():
	ser.reset_input_buffer()
	while ser.in_waiting == 0:
		None
	count = 0
	while True:
		if ser.read(1) == "":
			break
		count+=1
	return count

def save(filepath):
	import os, serial
	ser.reset_input_buffer()
	while ser.in_waiting == 0:
		None
	start_time = time.time()
	count = 0
	ser.timeout = 5
	with open(filepath, "w") as f:
		while True:
			print "reading... count:%d" % (count)
			c = ser.read(1)
			if c == "":
				break
			try:
				f.write(c)
			except:
				"Broken Stream"
			count+=1
	return "Transfered %d bytes in %d milliseconds (saved to %s)" % (count, (time.time()-start_time)*1000, filepath)

def send(filepath, bs=128):
	import os, serial
	size = os.stat(filepath).st_size
	read = 0
	sent = 0
	with open(filepath, "r") as f:
		while read < size:
			buf = f.read(bs)
			print "Sending " + str(bs) + " bytes... total: " + str(read+len(buf)) + "/" + str(size) + " bytes. "
			sent += ser.write(buf)
			read += bs
			while ser.read(4) != "OK\r\n":
				None

def transmit(string):
	import os, serial
	sent = 0
	sent += ser.write(string)
	while ser.read(4) != "OK\r\n":
		None
	print "Sent " + str(len(string)) + " bytes."
