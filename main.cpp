#include <iostream>

// #include "TcpSocket.h"
#include <string>
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"

using namespace std;

int main() {
	StringReverser* sr = new StringReverser();
	MyTestClientHandler<string, string>* mtch = new MyTestClientHandler<string, string>(sr);
	MySerialServer mss;
	mss.open(12345, mtch);
	delete sr;
	delete mtch;
	return 0;
}