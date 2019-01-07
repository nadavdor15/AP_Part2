#include <iostream>
#include <ostream>
#include <string>
#include <stdio.h>

#include "TcpSocket.h"
#include "SocketBuffer.h"

using namespace std;


int main() {
	TcpSocket tcpSocket;
	tcpSocket.bindSocket("0.0.0.0", 12345);
	tcpSocket.listenToClients(5);
	tcpSocket.acceptClient();
	ostream* os = tcpSocket.getOutputStream();
	os->operator<<("I am the king");
	return 0;
}