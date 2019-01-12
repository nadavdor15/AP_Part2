#ifndef MY_SERIAL_SERVER_H
#define MY_SERIAL_SERVER_H

#include "Server.h"
#include <thread>
#include <mutex>

using namespace server_side;

class MySerialServer : public Server {
	thread _t1;
	static bool _stopServer;
	static std::mutex _stopMutex;
	static void acceptClients(TcpSocket* socket, ClientHandler* clientHandler);

public:
	virtual void open(int port, ClientHandler* clientHandler);
	virtual void stop();
};

#endif