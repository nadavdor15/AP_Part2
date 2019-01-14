#ifndef SEARCH_SOLUTION_H
#define SEARCH_SOLUTION_H

#include "Solution.h"
#include "StringHelper.h"
#include <vector>

class SearchSolution : public Solution {
	std::vector<std::string> _path;
public:
	SearchSolution(std::vector<std::string> v): _path(v) {}

	SearchSolution(std::string str) {
		_path = StringHelper::split(str, ",");
	}

	virtual std::string toString() {
		std::string path = "";
		auto it = _path.begin();
		for (; it != --_path.end(); it++)
			path += *it + ",";
		path += *it;
		return path;
	}
};

#endif