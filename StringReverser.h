#ifndef STRING_REVERSER_H
#define STRING_REVERSER_H

#include "Solver.h"
#include "StringSolution.h"
#include <string>

class StringReverser : public Solver<std::string, StringSolution> {
public:
	virtual StringSolution* solve(std::string problem);
};

#endif