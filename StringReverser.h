#ifndef STRING_REVERSER_H
#define STRING_REVERSER_H

#include "Solver.h"
#include <string>

class StringReverser : public Solver<std::string, std::string> {
public:
	virtual std::string solve(std::string problem);
};

#endif