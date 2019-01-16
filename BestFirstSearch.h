#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include <vector>
#include <queue>
#include <map>
#include "Point.h"
#include "State.h"
#include "SearchSolution.h"
#include "Searcher.h"
#include <functional>
#include <algorithm>

struct MyComparator : public std::binary_function<State<Point>*, State<Point>*, bool>
{
    bool operator()(const State<Point>* lhs, const State<Point>* rhs) const
    {
        return lhs->getCost() > rhs->getCost();
    }
};

class BestFirstSearch : public Searcher<Point> {
	std::priority_queue<State<Point>*, std::vector<State<Point>*>, MyComparator> _open;
	std::map<State<Point>*, bool> _close;
public:
	virtual SearchSolution* search(Searchable<Point>* searchable) {
		State<Point>* start = searchable->getInitialState();
		State<Point>* goal = searchable->getGoalState();
		State<Point>* last = nullptr;
		_open.push(start);
		while (!_open.empty()) {
			State<Point>* minimal = _open.top();
			_open.pop();
			if (minimal->equals(*goal)) {
				minimal->setParent(last);
				break;
			} else {
				for (State<Point>* neighbor : searchable->getNeighbors(minimal)) {
					if (_close.find(neighbor) != _close.end()) {
						_close[neighbor] = true;
						_open.push(neighbor);
						neighbor->setParent(minimal);
					}
				}
				_close[minimal] = true;
			}
			last = minimal;
		}
		return new SearchSolution(searchable->getPath(goal));
	}
};

#endif