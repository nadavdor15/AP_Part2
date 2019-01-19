#ifndef FILE_CACHE_MANAGER_H
#define FILE_CACHE_MANAGER_H

#include "CacheManager.h"
#include "StringHelper.h"
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

template<class Problem, class Sol>
class FileCacheManager : public CacheManager<Problem, Sol> {
	std::map<std::string, std::string> _solutions;
	std::string _fileName;

	/*
	* Map file protocol:
	* <problemm>
	* \n$\n
	* <solition>
	* \n$$\n
	* the file must end with an empty line!
	* */
	void updateMap() {
		std::ifstream file(_fileName);
		std::string str(std::istreambuf_iterator<char>(file), {});
		str  = "\n" + str;
		str.erase(--str.end());
		std::vector<std::string> vec = StringHelper::split(str, "$$");
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			string key = *it;
			key.erase(key.begin());
			key.erase(--key.end());
			string value = *++it;
			value.erase(value.begin());
			value.erase(--value.end());
			_solutions.operator[](key) = value;
		}
		file.close();
	}

	void updateFile() {
		std::ofstream file(_fileName);
		for (auto it = _solutions.begin(); it != _solutions.end(); ++it) {
			std::string line = it->first + "\n$\n" + it->second + "\n$$\n" ;
			file << line;
		}
		file.close();
	}

public:
	FileCacheManager(const std::string fileName): _fileName(fileName) {
		this->updateMap();
	}

	bool hasSolution(Problem* problem) {
		return (_solutions.find(problem->toString()) != _solutions.end());
	}

	Sol* getSolution(Problem* problem) {
		if (!hasSolution(problem))
			throw "There is no solution for this problem";
		return new Sol(_solutions.at(problem->toString()));
	}

	void saveSolution(Problem* problem, Sol* sol) {
		if (hasSolution(problem)) {
			throw "This solution is already saved";
		}
		_solutions[problem->toString()] = sol->toString();
	}

	~FileCacheManager() {
		this->updateFile();
	}
};

#endif