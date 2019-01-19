#ifndef SOLVER_H
#define SOLVER_H

template<class Problem, class Sol>
class Solver {
public:
	virtual Sol* solve(Problem* problem) = 0;
	virtual ~Solver() {}
};

#endif