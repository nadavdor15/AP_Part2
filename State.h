#ifndef STATE_H
#define STATE_H

template<class T>
class State {
	double _cost;
	State<T>* _parent;
	T _value;
public:
	// CTOR
	State(T value) {
		_value = value;
	}

	// getters and setters:
	void setParent(State<T>* parent) {
		_parent = parent;
	}
	
	State<T>* getParent() {
		return _parent;
	}
	
	void setCost(double cost) {
		_cost = cost;
	}

	double getCost() {
		return _cost;
	}

	bool equals(State<T>* other) {
		return (this == other);
	}

	bool equals(State<T> other) {
		return (this == &other);
	}
};

#endif