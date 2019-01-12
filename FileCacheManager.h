#ifndef FILE_CACHE_MANAGER_H
#define FILE_CACHE_MANAGER_H

#include "CacheManager.h"
#include <thread>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
	std::map<std::string, std::string> _solutions;
	std::string _fileName;

	static void updateMap(std::string fileName, std::map<std::string, std::string>* solutions) {
		std::ifstream file(fileName);
		std::string line, key, value;
		while(getline(file, line)) {
			unsigned int index = line.find_first_of("$");
			if (index != std::string::npos) {
				key = line.substr(0, index);
				value = line.substr(index);
				solutions->at(key) = value;
			}
		}
		file.close();
	}

	void updateFile() {
		std::ofstream file(_fileName);
		for (auto it = _solutions.begin(); it != _solutions.end(); ++it) {
			std::string line = it->first + "$" + it->second;
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

	Solution getSolution(Problem problem) {
		if (!hasSolution(problem))
			throw "There is no solution for this problem";
		Solution s;
		std::stringstream ss;
		std::string stringProblem;
		ss << problem;
		getline(ss, stringProblem);
		ss.clear();
		ss << _solutions.at(stringProblem);
		getline(ss, s);
		return s;
	}

	void saveSolution(Problem problem, Solution solution) {
		if (hasSolution(problem)) {
			throw "This solution is already saved";
		}
		std::stringstream ss;
		std::string stringProblem;
		std::string stringSolution;
		ss << problem;
		getline(ss, stringProblem);
		ss.clear();
		ss << solution;
		getline(ss, stringSolution);
		_solutions[stringProblem] = stringSolution;
	}

	~FileCacheManager() {
		this->updateFile();
	}
};

#endif