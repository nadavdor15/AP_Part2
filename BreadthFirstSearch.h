#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H
#include "Searcher.h"
#include "SearchSolution.h"
#include <map>
#include <queue>

using std::map;
using std::queue;

template <class T>
class BreadthFirstSearch : public Searcher<T> {

public:
  SearchSolution* search(Searchable<T>* searchable) {
      queue<State<T>*> s;
      State<T>* current;
      State<T>* goal = searchable->getGoalState();
      State<T>* start = searchable->getInitialState();
      start->setParent(nullptr);
      map<State<T>*, bool> discovered;
      s.push(start);
      while (!s.empty()) {
          current = s.front();
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
  }};


#endif //   !BREADTH_FIRST_SEARCH_H
#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H
#include "Searcher.h"
#include "SearchSolution.h"
#include <map>
#include <queue>

using std::map;
using std::queue;

template <class T>
class BreadthFirstSearch : public Searcher<T> {

public:
  SearchSolution* search(Searchable<T>* searchable) {
      queue<State<T>*> s;
      State<T>* current;
      State<T>* goal = searchable->getGoalState();
      State<T>* start = searchable->getInitialState();
      start->setParent(nullptr);
      map<State<T>*, bool> discovered;
      s.push(start);
      while (!s.empty()) {
          current = s.front();
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
  }};


#endif //   !BREADTH_FIRST_SEARCH_H
