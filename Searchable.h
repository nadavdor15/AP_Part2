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
	State<T>* getInitialState() {
		return _initialState;
	}

	State<T>* getGoalState() {
		return _goalState;
	}

	virtual std::vector<std::string> getPath(State<T>* end) = 0;
	virtual std::vector<State<T>*> getNeighbors(State<T>* state) = 0;

	virtual ~Searchable() {}
};

#endif //	!SEARCHABLE_H