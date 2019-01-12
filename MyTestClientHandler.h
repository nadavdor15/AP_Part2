#ifndef MY_TEST_CLIENT_HANDLER_H
#define MY_TEST_CLIENT_HANDLER_H

#include "ClientHandler.h"
#include "Solver.h"

template <class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
	Solver<Problem, Solution>* _solver;
public:
	MyTestClientHandler(Solver<Problem, Solution>* solver): _solver(solver) {}
	virtual void handleClient(SockIS* sockIS, SockOS* SockOS) {
		string str;
		sockIS->operator>>(str);
		while (str.compare("end") != 0) {
			_solver->solve(str);
			// UPDATE CACHE
			sockIS->operator>>(str);

		}
	}
};

#endif