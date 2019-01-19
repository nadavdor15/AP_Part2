#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H
#include "Searcher.h"
#include "SearchSolution.h"
#include <stack>
#include <map>
#include <vector>
#include "State.h"

using std::stack;
using std::map;
using std::vector;

template <class T>
class DepthFirstSearch : public Searcher<T>{

public:
    virtual SearchSolution* search(Searchable<T>* searchable) {
      stack<State<T>*> s;
      State<T>* current;
      State<T>* goal = searchable->getGoalState();
      State<T>* start = searchable->getInitialState();
      map<State<T>*, bool> discovered;
      s.push(start);
      while (!s.empty()) {
          current = s.top();
          s.pop();
          // found our goal.
          if (current == goal)
              break;
          if (discovered.find(current) != discovered.end())
              continue;
          discovered[current] = true;
          vector<State<T>*> neighbors = searchable->getNeighbors(current);
          // search through all of it's neighbors.
          for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
              State<T>* son = *it;
              if (discovered.find(son) == discovered.end()) {
                  son->setParent(current);
                  s.push(son);
              }
          }
      }
      this->_numOfNodesEvaluated = discovered.size();
      return new SearchSolution(searchable->getPath(goal));
    }
};

#endif //   !DEPTH_FIRST_SEARCH_H
