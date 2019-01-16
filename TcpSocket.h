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
	TcpSocket(int socketID): _socketID(socketID) {}
	void bindSocket(string address, int port);
	void listenToClients(unsigned int clientNumber) const;
	int acceptClient();

	SockOS* getOutputStream() const {
		return _os;
	}

	SockIS* getInputStream() const {
		return _is;
	}

	int setTimeout(int sec, int usec = 0) {
		timeval timeout;
		timeout.tv_sec = sec;
		timeout.tv_usec = usec;
		return setsockopt(_socketID, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
	}

	void closeSocket();

	~TcpSocket();
};

#endif