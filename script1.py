from socket import socket
import time
s = socket()
s.connect(("127.0.0.1",12345))
time.sleep(0.5)
for i in range(5):
	s.send("1,2,3,4,5")
	time.sleep(0.5)
	print "sent", i+1, "row"
s.send("1,1")
time.sleep(0.5)
print "sent initialize"
s.send("1,1")
time.sleep(0.5)
print "sent goal"
s.send("end")
time.sleep(0.5)
print "send end, waiting for recv"
data = s.recv(1024)
print data
