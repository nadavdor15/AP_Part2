#ifndef MY_TEST_CLIENT_HANDLER_H
#define MY_TEST_CLIENT_HANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <sstream>
#include <iostream>

template <class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
	Solver<Problem, Solution>* _solver;
	CacheManager<Problem, Solution>* _cacheManager;
public:
	MyTestClientHandler(Solver<Problem, Solution>* solver,
						CacheManager<Problem, Solution>* cacheManager):
						_solver(solver), _cacheManager(cacheManager) {}

	virtual void handleClient(SockIS* sockIS, SockOS* SockOS) {
		string problem;
		while (sockIS->operator>>(problem) < 0) {}
		while (problem.compare("end") != 0) {
			std::stringstream ss;
			std::string stringSolution;
			Solution solution;
			if (_cacheManager->hasSolution(problem)) {
				std::cout << "Solution for problem: '" << problem << "' was found" << std::endl;
				try {
					solution = _cacheManager->getSolution(problem);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			} else {
				std::cout << "Solution for problem: '" << problem << "' was NOT found" << std::endl;
				solution = _solver->solve(problem);
				try {
					_cacheManager->saveSolution(problem, solution);
				} catch (const char* e) {
					std::cout << e << std::endl;
				}
			}
			ss << solution;
			getline(ss, stringSolution);
			SockOS->operator<<(stringSolution);
			while (sockIS->operator>>(problem) < 0) {}
		}
	}
};

#endif