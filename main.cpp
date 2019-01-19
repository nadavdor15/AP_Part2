#include "FileCacheManager.h"
#include "MyParallelServer.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "SearchSolver.h"
#include "BestFirstSearch.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "AStarSearch.h"
#include "Point.h"

using namespace std;

int main(int argc, char* argv[]) {
	Server* server = new MyParallelServer();
	Searcher<Point>* searcher = new AStarSearch<Point>();
	Solver<SearchableMatrix, SearchSolution>* solver = new SearchSolver<Point>(searcher);
	CacheManager<SearchableMatrix, SearchSolution>* cacheManager = new FileCacheManager<SearchableMatrix, SearchSolution>("sol.txt");
	ClientHandler* clientHandler = new MyClientHandler<SearchableMatrix, SearchSolution>(solver, cacheManager);
	server->open(stoi(argv[1]), clientHandler);
	delete server;
	delete clientHandler;
	delete solver;
	delete searcher;
	delete cacheManager;
	return 0;
}

// int main(int argc, char* argv[]) {
// 	Server* server = new MyParallelServer();
// 	Solver<StringDecorator, StringDecorator>* solver = new StringReverser();
// 	CacheManager<StringDecorator, StringDecorator>* cacheManager = new FileCacheManager<StringDecorator, StringDecorator>("sol.txt");
// 	ClientHandler* clientHandler = new MyTestClientHandler<StringDecorator, StringDecorator>(solver, cacheManager);
// 	server->open(stoi(argv[1]), clientHandler);
// 	delete server;
// 	delete solver;
// 	delete cacheManager;
// 	delete clientHandler;
// 	return 0;
// }