#include "MySerialServer.h"
#include <errno.h>
#include <iostream>
#include <mutex>

bool volatile MySerialServer::_stopServer;

void MySerialServer::open(int port, ClientHandler* clientHandler) {
	_socket.bindSocket("", port);
	_socket.listenToClients(5);
	_socket.setTimeout(60);
	_t1 = thread(acceptClients, &_socket, clientHandler);
	_t1.join();
}

void MySerialServer::stop() {
	_stopServer = true;
	_socket.closeSocket();
}

void MySerialServer::acceptClients(TcpSocket* socket, ClientHandler* clientHandler) {
	_stopServer = false;
	while (!_stopServer) {
		if (socket->acceptClient() < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				// std::cout << "Timeout on accept" << std::endl;
				_stopServer = true;
				break;
			} else {
				std::cout << "Unknown error on accept" << std::endl;
				exit(1);
			}
		}
		SockIS* is = socket->getInputStream();
		SockOS* os = socket->getOutputStream();
		clientHandler->handleClient(is, os);
	}
}