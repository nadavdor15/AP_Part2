#include <string>
#include <iostream>
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "SearchableMatrix.h"

using namespace std;

// int main(int argc, char* argv[]) {
// 	SearchableMatrix* matrix = new SearchableMatrix("1,2,3\n4,5,6\n7,8,9\n0,0\n2,2");
// 	cout << "Output: \n" << matrix->toString() << endl;
// 	delete matrix;
// 	return 0;
// }

int main(int argc, char* argv[]) {
	MyParallelServer mps;
	StringReverser* sr = new StringReverser();
	CacheManager<StringDecorator, StringDecorator>* cm = new FileCacheManager<StringDecorator, StringDecorator>("sol.txt");
	MyTestClientHandler<StringDecorator, StringDecorator>* mtch = new MyTestClientHandler<StringDecorator, StringDecorator>(sr, cm);
	mps.open(stoi(argv[1]), mtch);
	// cout << "check" << endl;
	delete sr;
	delete cm;
	delete mtch;
	return 0;
}