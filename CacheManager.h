#ifndef CHACHE_MANAGER_H
#define CHACHE_MANAGER_H

template<class Problem, class Solution>
class CacheManager {

public:
	virtual bool hasSolution(Problem problem) = 0;
	virtual Solution getSolution(Problem problem) = 0;
	virtual void saveSolution(Problem problem, Solution solution) = 0;
	virtual ~CacheManager() {}
};

#endif