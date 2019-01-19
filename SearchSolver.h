#ifndef SEARCH_SOLVER_H
#define SEARCH_SOLVER_H

#include "Searcher.h"
#include "SearchableMatrix.h"
#include "SearchSolution.h"
#include "Solver.h"

// problem is searchable.
template<class T>
class SearchSolver : public Solver<SearchableMatrix, SearchSolution> {
	Searcher<T>* _searcher;
public:
	SearchSolver(Searcher<T>* searcher): _searcher(searcher) {}

	virtual SearchSolution* solve(SearchableMatrix* searchable) {
		return _searcher->search(searchable);
	}
};

#endif //	!SEARCH_SOLVER_H