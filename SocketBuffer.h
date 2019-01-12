#ifndef SOCKET_BUFFER_H
#define SOCKET_BUFFER_H

#include <iostream>
#include <ostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>

#include <sstream>

using namespace std;

class SocketBuffer : public streambuf {
	int _sockID;

public:
	SocketBuffer(int sockID): _sockID(sockID) {}

	// sending with \r\n at the end of the string we received
	virtual streamsize xsputn(const char* s, streamsize n) override;

	// sending without \r\n along with the char
	virtual streambuf::int_type overflow(streambuf::int_type c) override {
		return send(_sockID, &c, 2, 0);
	}

	virtual streamsize xsgetn(char_type* __s, streamsize __n) override;
};

#endif