#ifndef STATE_H
#define STATE_H

#include <iostream>

template<class T>
class State {
protected:
	double _cost;
	T _value;
	State<T>* _parent;
public:
	// CTOR
	State(): _parent(nullptr) {}

	State(T value): _value(value), _parent(nullptr) {}

	State(const State<T>& state) {
		_cost = state.getCost();
		_value = state.getValue();
		_parent = state.getParent();
	}

	// getters and setters:
	void setParent(State<T>* parent) {
		_parent = parent;
	}
	
	State<T>* getParent() const {
		return _parent;
	}

	T getValue() const {
		return _value;
	}
	
	void setCost(double cost) {
		_cost = cost;
	}

	double getCost() const {
		return _cost;
	}

	bool operator==(const State<T> other) {
		return (_value == other.getValue());
	}

	bool equals(const State<T>* other) {
		return (_value == other->getValue());
	}

	bool equals(const State<T> other) const {
		return (_value == other.getValue());
	}

	bool operator<(const State<T>& other) const {
		return !(_value == other.getValue());
	}

	bool operator!=(const State<T>& other) const {
		return !this->operator==(other);
	}
};

#endif