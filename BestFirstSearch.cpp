#include "BestFirstSearch.h"

SearchSolution* BestFirstSearch::search(Searchable<Point>* searchable) {
	_numOfNodesEvaluated = 0;
	State<Point>* start = searchable->getInitialState();
	State<Point>* goal = searchable->getGoalState();
	_open.push(start, start->getCost());
	++_numOfNodesEvaluated;
	while (!_open.empty()) {
		State<Point>* minimal = _open.pop();
		_close.push(minimal, searchable->getPathCost(minimal));
		if (minimal->equals(goal))
			break;
		else
			for (State<Point>* neighbor : searchable->getNeighbors(minimal)) {
				++_numOfNodesEvaluated;
				int previousCost = searchable->getPathCost(neighbor);
				int newCost = searchable->getPathCost(minimal) + neighbor->getCost();
				if (!_close.exists(neighbor) && !_open.exists(neighbor)) {
					neighbor->setParent(minimal);
					_open.push(neighbor, searchable->getPathCost(neighbor));
				} else if (newCost < previousCost) {
					neighbor->setParent(minimal);
					_open.push(neighbor, newCost);
				}
			}
	}
	return new SearchSolution(searchable->getPath(goal));
}