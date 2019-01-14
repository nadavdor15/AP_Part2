#ifndef STRING_SOLUTION_H
#define STRING_SOLUTION_H

#include "Solution.h"
#include <string>

class StringSolution : public Solution {
	std::string _str;

public:
	// CTOR
	StringSolution(std::string str) {
		_str = str;
	}

	virtual std::string toString() {
		return _str;
	}
};

#endif //	!STRING_SOLUTION_H