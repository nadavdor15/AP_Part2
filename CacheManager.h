#ifndef CHACHE_MANAGER_H
#define CHACHE_MANAGER_H

template<class Problem, class Sol>
class CacheManager {

public:
	virtual bool hasSolution(Problem* problem) = 0;
	virtual Sol* getSolution(Problem* problem) = 0;
	virtual void saveSolution(Problem* problem, Sol* sol) = 0;
	virtual ~CacheManager() {}
};

#endif