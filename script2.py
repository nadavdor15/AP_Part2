from socket import socket
s = socket()
s.connect(("127.0.0.1",12346))
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,2,3,4,5,6,7,8")
s.send("1,1")
s.send("5,6")
s.send("end")
data = s.recv(1024)
print data
