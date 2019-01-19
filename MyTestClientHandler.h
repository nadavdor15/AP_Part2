#ifndef MY_TEST_CLIENT_HANDLER_H
#define MY_TEST_CLIENT_HANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <iostream>

template <class Problem, class Sol>
class MyTestClientHandler : public ClientHandler {
	Solver<Problem, Sol>* _solver;
	CacheManager<Problem, Sol>* _cacheManager;
public:
	MyTestClientHandler(Solver<Problem, Sol>* solver,
						CacheManager<Problem, Sol>* cacheManager):
						_solver(solver), _cacheManager(cacheManager) {}

	virtual void handleClient(SockIS* sockIS, SockOS* sockOS) {
		string problem = "";
		while (sockIS->operator>>(problem) < 0) {}
		while (problem.compare("end") != 0) {
			Sol* sol;
			Problem* prob = new Problem(problem);
			if (_cacheManager->hasSolution(prob)) {
				try {
					sol = _cacheManager->getSolution(prob);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			} else {
				sol = _solver->solve(prob);
				try {
					_cacheManager->saveSolution(prob, sol);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			}
			sockOS->operator<<(sol->toString());
			delete sol;
			delete prob;
			while (sockIS->operator>>(problem) < 0) {}
		}
	}
};

#endif