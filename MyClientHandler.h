#ifndef MY_CLIENT_HANDLER_H
#define MY_CLIENT_HANDLER_H 

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <iostream>

using std::cout;
using std::endl;

template <class Problem, class Sol>
class MyClientHandler : public ClientHandler {
	Solver<Problem, Sol>* _solver;
	CacheManager<Problem, Sol>* _cacheManager;
public:
	MyClientHandler(Solver<Problem, Sol>* solver,
						CacheManager<Problem, Sol>* cacheManager):
						_solver(solver), _cacheManager(cacheManager) {}

	virtual void handleClient(SockIS* sockIS, SockOS* sockOS) {
		string input = "", problem = "";
		while (sockIS->operator>>(input) < 0) {}
		while (input.compare("end") != 0) {
			problem += input + "\n";
			while (sockIS->operator>>(input) < 0) {}
		}
		problem.erase(--problem.end());
		Sol* sol;
		Problem* prob = new Problem(problem);
		if (_cacheManager->hasSolution(prob)) {
			try {
				cout << "Solution was found" << endl;
				sol = _cacheManager->getSolution(prob);
			} catch (const char* e) {
				cout << e << endl;
			}
		} else {
			cout << "No solution found" << endl;
			sol = _solver->solve(prob);
			try {
				_cacheManager->saveSolution(prob, sol);
			} catch (const char* e) {
				cout << e << endl;
			}
		}
		sockOS->operator<<(sol->toString());
		delete sol;
		delete prob;
	}
};

#endif