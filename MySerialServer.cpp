#include "MySerialServer.h"
#include "stdio.h"
#include <iostream>

void MySerialServer::open(int port, ClientHandler* clientHandler) {
	_socket.bindSocket("", port);
	_socket.listenToClients(5);
	_t1 = thread(acceptClients, &_socket, clientHandler);
	_t1.join();
}

void MySerialServer::stop() {

}

void MySerialServer::acceptClients(TcpSocket* socket, ClientHandler* clientHandler) {
	while (true) {
		socket->acceptClient();
		SockIS* is = socket->getInputStream();
		SockOS* os = socket->getOutputStream();
		clientHandler->handleClient(is, os);
	}
}