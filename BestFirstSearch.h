#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Point.h"
#include "State.h"
#include "SearchSolution.h"
#include "Searcher.h"
#include "MyPriorityQueue.h"

class BestFirstSearch : public Searcher<Point> {
	MyPriorityQueue<State<Point>*> _open;
	MyPriorityQueue<State<Point>*> _close;
public:
	virtual SearchSolution* search(Searchable<Point>* searchable);
};

#endif