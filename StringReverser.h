#ifndef STRING_REVERSER_H
#define STRING_REVERSER_H

#include "Solver.h"
#include "Solution.h"
#include <string>

class StringDecorator : public Solution {
	std::string _str;
public:
	StringDecorator(std::string str): _str(str) {}

	std::string toString() {
		return _str;
	}
};

class StringReverser : public Solver<StringDecorator, StringDecorator> {
public:
	virtual StringDecorator* solve(StringDecorator problem);
};

#endif