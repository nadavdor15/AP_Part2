#ifndef MY_PARALLEL_SERVER_H
#define MY_PARALLEL_SERVER_H

#include "Server.h"
#include "TasksQueue.h"
#include <thread>
#include <queue>

using namespace server_side;

class MyParallelServer : public Server {
	static TasksQueue _tasksQueue;
	std::queue<std::thread> _workers;
	std::thread _t1;
	static volatile bool _stopServer;
	static void work(TasksQueue* tasksQueue);
	static void acceptClients(TcpSocket* socket, ClientHandler* clientHandler, int* returnVal);

public:
	MyParallelServer();
	virtual void open(int port, ClientHandler* clientHandler);
	virtual void stop();
	virtual ~MyParallelServer() {
		this->stop();
	}
};

#endif