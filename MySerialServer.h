#ifndef MY_SERIAL_SERVER_H
#define MY_SERIAL_SERVER_H

#include "Server.h"
#include <thread>

using namespace server_side;

class MySerialServer : public Server {
	thread _t1;
	static void acceptClients(TcpSocket* socket, ClientHandler* clientHandler);

public:
	virtual void open(int port, ClientHandler* clientHandler);
	virtual void stop();
};

#endif