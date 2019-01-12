#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <istream>
#include <ostream>
#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include "SocketBuffer.h"
#include "SockIOS.h"

using namespace std;

class TcpSocket {
	int _socketID = -1;
	struct sockaddr_in _serv_addr, _cli_addr;
	SockOS* _os;
	SockIS* _is;

public:
	TcpSocket();
	void bindSocket(string address, int port);
	void listenToClients(unsigned int clientNumber) const;
	int acceptClient();

	SockOS* getOutputStream() const {
		return _os;
	}

	SockIS* getInputStream() const {
		return _is;
	}

	void closeSocket();
	~TcpSocket();
};

#endif