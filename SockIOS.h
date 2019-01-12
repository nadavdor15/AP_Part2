#ifndef SOCK_IOS_H
#define SOCK_IOS_H

#include <stdio.h>
#include <string.h>
#include <istream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#define POINTER_SIZE 64

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

	int operator<<(string& str) {
		stringstream ss;
		const char* t = str.c_str();
		ss << (void*) t;
		string s;
		getline(ss, s);
		t = s.c_str();
		char arr[POINTER_SIZE + 1];
		strncpy(arr, t, POINTER_SIZE + 1);
		arr[POINTER_SIZE + 1] = '\0';
		return this->rdbuf()->sputn(arr, str.length() + 1);
	}
};

#endif