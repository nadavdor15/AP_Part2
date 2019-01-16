#include "MyParallelServer.h"
#include "ClientHandlerTask.h"
#include <errno.h>
#include <future>
#include <iostream>

#define NUMBER_OF_THREADS 5

bool volatile MyParallelServer::_stopServer;
TasksQueue MyParallelServer::_tasksQueue;

MyParallelServer::MyParallelServer() {
	for (int i = 0; i < NUMBER_OF_THREADS; ++i)
		_workers.emplace(work, &_tasksQueue);
}

void MyParallelServer::work(TasksQueue* tasksQueue) {
	while (!tasksQueue->stop()) {
		tasksQueue->wait();
		Task* task = tasksQueue->pop();
		if (task != nullptr) {
			task->execute();
			delete task;
		}
	}
}

void MyParallelServer::open(int port, ClientHandler* clientHandler) {
	_socket.bindSocket("", port);
	_socket.listenToClients(5);
	_socket.setTimeout(10);
	int returnVal = 1;
	_t1 = thread(acceptClients, &_socket, clientHandler, &returnVal);
	_t1.join();
	if (returnVal == -1)
		this->stop();
}

void MyParallelServer::stop() {
	if (_stopServer == false) {
		_stopServer = true;
		_tasksQueue.exit();
		while (!_workers.empty()) {
			_workers.front().join();
			_workers.pop();
		}
	}
}

void MyParallelServer::acceptClients(TcpSocket* socket, ClientHandler* clientHandler, int* returnVal) {
	_stopServer = false;
	bool handledFirst = false;
	while (!_stopServer) {
		if (socket->acceptClient() < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				// std::cout << "Timeout on accept" << std::endl;
				if (!handledFirst) {
					continue;
				}
				*returnVal = -1;
				break;
			} else {
				std::cout << "Unknown error on accept" << std::endl;
				exit(1);
			}
		}
		handledFirst = true;
		Task* task = new ClientHandlerTask(clientHandler, socket);
		_tasksQueue.push(task);
	}
}