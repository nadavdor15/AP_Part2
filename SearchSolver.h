#ifndef SEARCH_SOLVER_H
#define SEARCH_SOLVER_H

#include "Searcher.h"
#include "SearchSolution.h"
#include "Solver.h"

// problem is searchable.
template<class T>
class SearchSolver : public Solver<Searchable<T>, SearchSolution> {
	/*
		virtual Solution solve(Problem problem) = 0;
	virtual ~Solver() {}
	*/
	Searcher<T>* _searcher;
public:
	SearchSolver(Searcher<T>* searcher): _searcher(searcher) {}

	virtual SearchSolution* solve(Searchable<T> searchable) {
		return _searcher->search(searchable);
	}
};

#endif //	!SEARCH_SOLVER_H