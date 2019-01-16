#ifndef CLIENT_HANDLER_TASK_H
#define CLIENT_HANDLER_TASK_H

#include "TasksQueue.h"
#include "ClientHandler.h"
#include "TcpSocket.h"

class ClientHandlerTask : public Task {
	ClientHandler* _clientHandler;
	TcpSocket* _socket;
public:
	ClientHandlerTask(ClientHandler* clientHandler,
					  TcpSocket* socket):
					  _clientHandler(clientHandler),
					  _socket(socket) {}

	void execute() {
		SockOS* os = _socket->getOutputStream();
		SockIS* is = _socket->getInputStream();
		_clientHandler->handleClient(is, os);
	}
};

#endif