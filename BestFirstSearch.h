#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "SearchSolution.h"
#include "Searcher.h"
#include "MyPriorityQueue.h"

template<class T>
class BestFirstSearch : public Searcher<T> {
public:
	virtual SearchSolution* search(Searchable<T>* searchable) {
		MyPriorityQueue<State<T>*> open;
		MyPriorityQueue<State<T>*> close;
		State<T>* start = searchable->getInitialState();
		State<T>* goal = searchable->getGoalState();
		open.push(start, start->getCost());
		while (!open.empty()) {
			State<T>* minimal = open.pop();
			close.push(minimal, searchable->getPathCost(minimal));
			if (minimal->equals(goal))
				break;
			else
				for (State<T>* neighbor : searchable->getNeighbors(minimal)) {
					int previousCost = searchable->getPathCost(neighbor);
					int newCost = searchable->getPathCost(minimal) + neighbor->getCost();
					if (!close.exists(neighbor) && !open.exists(neighbor)) {
						neighbor->setParent(minimal);
						open.push(neighbor, searchable->getPathCost(neighbor));
					} else if (newCost < previousCost) {
						neighbor->setParent(minimal);
						open.push(neighbor, newCost);
					}
				}
		}
		Searcher<T>::_numOfNodesEvaluated = close.size();
		return new SearchSolution(searchable->getPath(goal));
	}
};

#endif