#include <string>
#include <iostream>
#include "StringSolution.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	MySerialServer mss;
	StringReverser* sr = new StringReverser();
	CacheManager<string, StringSolution>* cm = new FileCacheManager<string, StringSolution>("sol.txt");
	MyTestClientHandler<string, StringSolution>* mtch = new MyTestClientHandler<string, StringSolution>(sr, cm);
	mss.open(stoi(argv[1]), mtch);
	delete sr;
	delete cm;
	delete mtch;
	return 0;
}