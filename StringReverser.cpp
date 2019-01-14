#include <iostream>
#include "StringReverser.h"
#include "StringSolution.h"

StringSolution* StringReverser::solve(std::string problem) {
	int length = problem.length();
	std::string solution(problem);
	for (int i = 0; i <= length; i++) {
		solution[i] = problem[length - i - 1];
	}
	return new StringSolution(solution);
}