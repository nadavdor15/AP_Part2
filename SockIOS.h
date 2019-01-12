#ifndef SOCK_IOS_H
#define SOCK_IOS_H

#include <istream>
#include <ostream>
#include <string>

using namespace std;

class SockIS : public istream {
public:
	SockIS(streambuf* streamBuf): istream(streamBuf) {}

	int operator>>(string& str) {
		char buf[2048];
		int bytesReceived = this->rdbuf()->sgetn(buf, 2048);
		str = std::string(buf);
		return bytesReceived;
	}
};


class SockOS : public ostream {
public:
	SockOS(streambuf* streamBuf): ostream(streamBuf) {}
};

#endif