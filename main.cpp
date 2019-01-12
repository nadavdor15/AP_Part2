#include <string>
#include <iostream>
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	MySerialServer mss;
	StringReverser* sr = new StringReverser();
	CacheManager<string, string>* cm = new FileCacheManager<string, string>("sol.txt");
	MyTestClientHandler<string, string>* mtch = new MyTestClientHandler<string, string>(sr, cm);
	mss.open(stoi(argv[1]), mtch);
	delete sr;
	delete cm;
	delete mtch;
	return 0;
}