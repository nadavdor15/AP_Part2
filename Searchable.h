#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include "State.h"
#include <vector>
#include <string>

template<class T>
class Searchable {
protected:
	State<T>* _initialState;
	State<T>* _goalState;

public:
	State<T>* getInitialState() const {
		return _initialState;
	}

	State<T>* getGoalState() const {
		return _goalState;
	}

	virtual std::vector<State<T>*> getNeighbors(State<T>* state) const = 0;
	virtual std::vector<std::string> getPath(State<T>* end) const = 0;
	virtual double getPathCost(State<T>* state) const = 0;
	virtual double getEstimatedCostToEnd(State<T>* state) const = 0;
	virtual ~Searchable() {}
};

#endif //	!SEARCHABLE_H
