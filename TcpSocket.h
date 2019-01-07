#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

// #define _BSD_SOURCE
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

using namespace std;

class TcpSocket {
	int _socketID;
	struct sockaddr_in _serv_addr, _cli_addr;
	ostream* _os;
	istream* _is;

public:
	TcpSocket() {
		_socketID = socket(AF_INET, SOCK_STREAM, 0);
		if (_socketID < 0) {
			perror("Could not open socket");
			exit(1);
		}
		cout << "Socket is now open" << endl;
	}

	void bindSocket(string address, int port);

	void listenToClients(unsigned int clientNumber) const {
		if (listen(_socketID, clientNumber) < 0) {
			perror("Socket could not listen");
			exit(1);
		}
		cout << "Server is now listenting to " << clientNumber << " clients" << endl;
	}

	int acceptClient();

	ostream* getOutputStream() const {
		return _os;
	}

	istream* getInputStream() const {
		return _is;
	}

	~TcpSocket() {
		delete _os->rdbuf(); // deleting the streambuf we gave _os in c'tor
		delete _os;
		// delete _is;
	}
};

#endif