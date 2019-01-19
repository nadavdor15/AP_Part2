#include <iostream>
#include "StringReverser.h"

StringDecorator* StringReverser::solve(StringDecorator* problem) {
	int length = problem->toString().length();
	std::string solutionString = problem->toString();
	std::string problemString(solutionString);
	for (int i = 0; i < length; i++) {
		solutionString[i] = problemString[length - i - 1];
	}
	return new StringDecorator(solutionString);
}