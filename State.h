#ifndef STATE_H
#define STATE_H

template<class T>
class State {
	double _cost;
	T _value;
	State<T>* _parent;
public:
	// CTOR
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

	bool equals(State<T> other) {
		return (this->_value == other.getValue());
	}

	// THE OPPOSITE OF < in purose
	bool operator<(const State<T>& other) const {
		return _value > other.getValue();
	}
};

#endif