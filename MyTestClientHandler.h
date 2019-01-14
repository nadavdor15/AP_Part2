#ifndef MY_TEST_CLIENT_HANDLER_H
#define MY_TEST_CLIENT_HANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <sstream>
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
		string problem;
		while (sockIS->operator>>(problem) < 0) {}
		while (problem.compare("end") != 0) {
			Sol* sol;
			if (_cacheManager->hasSolution(problem)) {
				std::cout << "Solution for problem: '" << problem << "' was found" << std::endl;
				try {
					sol = _cacheManager->getSolution(problem);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			} else {
				std::cout << "Solution for problem: '" << problem << "' was NOT found" << std::endl;
				sol = _solver->solve(problem);
				try {
					_cacheManager->saveSolution(problem, sol);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			}
			sockOS->operator<<(sol->toString());
			delete sol;
			while (sockIS->operator>>(problem) < 0) {}
		}
	}
};

#endif