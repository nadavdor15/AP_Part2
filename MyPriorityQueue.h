#ifndef MY_PRIORITY_QUEUE
#define MY_PRIORITY_QUEUE 

#include <map>
#include <cmath>

template<class T>
class MyPriorityQueue {
	std::map<T, double> _queue;
	T _minimumObject;
	double _minimumValue;
public:
	MyPriorityQueue(): _minimumObject(nullptr), _minimumValue(NAN) {}

	void push(T& obj, const double value) {
		_queue[obj] = value;
		if (value < _minimumValue) {
			_minimumObject = obj;
			_minimumValue = value;
		}
		else if (std::isnan(_minimumValue)) {
			_minimumObject = obj;
			_minimumValue = value;
		}
	}

	const T pop() {
		if (_queue.empty())
			throw "The priority queue is empty";
		T prevMinimum = _minimumObject;
		_queue.erase(_minimumObject);
		_minimumObject = _queue.begin()->first;
		_minimumValue = _queue.begin()->second;
		for (auto pair : _queue) {
			if (pair.second < _minimumValue) {
				_minimumObject = pair.first;
				_minimumValue = pair.second;
			}
		}
		if (_queue.empty()) {
			_minimumObject = nullptr;
			_minimumValue = NAN;
		}
		return prevMinimum;
	}

	bool exists(T& obj) const {
		try {
			_queue.at(obj);
			return 1;
		} catch (...) {
			return 0;
		}
	}

	bool empty() const {
		return _queue.empty();
	}

	int size() const {
		return _queue.size();
	}
};

#endif