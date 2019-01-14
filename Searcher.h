#ifndef SEARCHER_H
#define SEARCHER_H 

#include "Solution.h"
#include "Searchable.h"

template<class T>
class Searcher {
protected:
	int _numOfNodesEvaluated;

public:
	virtual Solution* search(Searchable<T>* searchable) = 0;
	int getNumOfNodesEvaluated() {
		return _numOfNodesEvaluated;
	}
	virtual ~Searcher() {}
};

#endif //	!SEARCHER_H