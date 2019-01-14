#ifndef FILE_CACHE_MANAGER_H
#define FILE_CACHE_MANAGER_H

#include "CacheManager.h"
#include <thread>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

template<class Problem, class Sol>
class FileCacheManager : public CacheManager<Problem, Sol> {
	std::map<std::string, std::string> _solutions;
	std::string _fileName;

	static void updateMap(std::string fileName, std::map<std::string, std::string>* solutions) {
		std::ifstream file(fileName);
		std::string line, key, value;
		while(getline(file, line)) {
			unsigned int index = line.find_first_of("$");
			if (index != std::string::npos) {
				key = line.substr(0, index);
				value = line.substr(index + 1);
				solutions->operator[](key) = value;
			}
		}
		file.close();
	}

	void updateFile() {
		std::ofstream file(_fileName);
		for (auto it = _solutions.begin(); it != _solutions.end(); ++it) {
			std::string line = it->first + "$" + it->second + "\n";
			file << line;
		}
		file.close();
	}

public:
	FileCacheManager(const std::string fileName): _fileName(fileName) {
		std::thread t1(this->updateMap, fileName, &_solutions);
		t1.detach();
	}

	bool hasSolution(Problem problem) {
		std::string stringProblem;
		std::stringstream ss;
		ss << problem;
		getline(ss, stringProblem);
		return (_solutions.find(stringProblem) != _solutions.end());
	}

	Sol* getSolution(Problem problem) {
		if (!hasSolution(problem))
			throw "There is no solution for this problem";
		std::stringstream ss;
		std::string stringProblem;
		ss << problem;
		getline(ss, stringProblem);
		return new Sol(_solutions.at(stringProblem));
	}

	void saveSolution(Problem problem, Sol* sol) {
		if (hasSolution(problem)) {
			throw "This solution is already saved";
		}
		std::stringstream ss;
		std::string stringProblem;
		std::string stringSol = sol->toString();
		ss << problem;
		getline(ss, stringProblem);
		_solutions[stringProblem] = stringSol;
	}

	~FileCacheManager() {
		this->updateFile();
	}
};

#endif