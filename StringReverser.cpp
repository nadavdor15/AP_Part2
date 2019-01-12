#include "StringReverser.h"
#include <iostream>

std::string StringReverser::solve(std::string problem) {
	int length = problem.length();
	std::string solution(problem);
	for (int i = 0; i <= length; i++) {
		solution[i] = problem[length - i - 1];
	}
	return solution;
}