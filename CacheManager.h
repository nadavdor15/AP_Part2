#ifndef CHACHE_MANAGER_H
#define CHACHE_MANAGER_H

template<class Problem, class Solution>
class CacheManager {

public:
	bool hasSolution(Problem problem);
	Solution getSolution(Problem problem);
	bool saveSolution(Problem problem, Solution solution);
};

#endif