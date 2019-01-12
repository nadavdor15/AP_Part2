#include "StringReverser.h"
#include <iostream>

std::string StringReverser::solve(std::string problem) {
	std::cout << "Problem: '" << problem << "'" << std::endl;
	int length = problem.length();
	std::string solution(problem);
	for (int i = 0; i <= length; i++) {
		solution[i] = problem[length - i - 1];
	}
	std::cout << "Solution: '" << solution << "'" << std::endl;
	return solution;
}