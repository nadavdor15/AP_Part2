#include "MySerialServer.h"
#include <errno.h>
#include <iostream>
#include <mutex>

bool MySerialServer::_stopServer;
std::mutex MySerialServer::_stopMutex;

void MySerialServer::open(int port, ClientHandler* clientHandler) {
	_socket.bindSocket("", port);
	_socket.listenToClients(5);
	_socket.setTimeout(10);
	std::lock_guard<std::mutex> lock(_stopMutex);
	_stopServer = false;
	_t1 = thread(acceptClients, &_socket, clientHandler);
	// _t1.detach();
	_t1.join();
}

void MySerialServer::stop() {
	std::lock_guard<std::mutex> lock(_stopMutex);
	_stopServer = true;
	_socket.closeSocket();
}

void MySerialServer::acceptClients(TcpSocket* socket, ClientHandler* clientHandler) {
	while (!_stopServer) {
		if (socket->acceptClient() < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				std::lock_guard<std::mutex> lock(_stopMutex);
				std::cout << "Timeout on accept" << std::endl;
				_stopServer = false;
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