#ifndef SERVER_H
#define SERVER_H

#include "ClientHandler.h"
#include "TcpSocket.h"

namespace server_side {
	class Server {
	protected:
		TcpSocket _socket;
	public:
		virtual void open(int port, ClientHandler* clientHandler) = 0;
		virtual void stop() = 0;
		virtual ~Server() {}
	};
};

#endif