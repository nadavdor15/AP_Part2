#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include "SearchSolution.h"
#include "Searcher.h"
#include "MyPriorityQueue.h"

template<class T>
class AStarSearch : public Searcher<T> {
public:
	virtual SearchSolution* search(Searchable<T>* searchable) {
		MyPriorityQueue<State<T>*> open;
		MyPriorityQueue<State<T>*> close;
		State<T>* start = searchable->getInitialState();
		State<T>* goal = searchable->getGoalState();
		open.push(start, start->getCost() + searchable->getEstimatedCostToEnd(start));
		while (!open.empty()) {
			State<T>* minimal = open.pop();
			close.push(minimal, searchable->getPathCost(minimal) + searchable->getEstimatedCostToEnd(minimal));
			if (minimal->equals(goal))
				break;
			for (State<T>* neighbor : searchable->getNeighbors(minimal)) {
				int previousCost = searchable->getPathCost(neighbor);
				int newCost = searchable->getPathCost(minimal) + neighbor->getCost();
				if (open.exists(neighbor)) {
					if (newCost >= previousCost)
						continue;
				} else if (close.exists(neighbor)) {
					if (newCost >= previousCost)
						continue;
					State<T>* poped = close.pop();
					open.push(poped, newCost + searchable->getEstimatedCostToEnd(poped));
				} else
					open.push(neighbor, previousCost + searchable->getEstimatedCostToEnd(neighbor));
				neighbor->setParent(minimal);
			}
		}
		Searcher<T>::_numOfNodesEvaluated = close.size();
		return new SearchSolution(searchable->getPath(goal));
	}
};

#endif