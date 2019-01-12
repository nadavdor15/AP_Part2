#ifndef SOLVER_H
#define SOLVER_H

template<class Problem, class Solution>
class Solver {
public:
	virtual Solution solve(Problem problem) = 0;
	virtual ~Solver() {}
};

#endif