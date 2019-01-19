#ifndef SEARCHABLE_MATRIX_H
#define SEARCHABLE_MATRIX_H 

#include "Searchable.h"
#include "StringHelper.h"
#include "Point.h"
#include <string>
#include <vector>
#include <cmath>

#include <iostream>

class SearchableMatrix : public Searchable<Point> {
	std::vector<std::vector<State<Point>*>> _cells;
	int _rows, _cols;
public:
	SearchableMatrix(const std::string str) {
		// generating rows
		std::vector<std::string> rows = StringHelper::split(str, "\n");
		// generating indexes for initialize and goal states
		std::vector<std::string> endPoint = StringHelper::split(rows.back(), ",");
		rows.erase(--rows.end());
		std::vector<std::string> startPoint = StringHelper::split(rows.back(), ",");
		rows.erase(--rows.end());
		// for each row we add it's states to the matrix _cells
		int i = 0, j;
		for (std::string row : rows) {
			std::vector<State<Point>*> singleRow;
			j = 0;
			for (std::string s : StringHelper::split(row, ",")) {
				State<Point>* state = new State<Point>(Point(i, j));
				state->setCost(std::stod(s));
				singleRow.push_back(state);
				j++;
			}
			_cells.push_back(singleRow);
			i++;
		}
		// detemining sizes of the matrix
		_rows = rows.size();
		_cols = _cells[0].size();
		// getting the initialize and goal states by the indexes
		try {
			_initialState = (_cells.begin() + std::stoi(startPoint[0]))->at(std::stoi(startPoint[1]));
			_goalState = (_cells.begin() + std::stoi(endPoint[0]))->at(std::stoi(endPoint[1]));
		} catch (...) {
			std::cout << "Problem with initial and goal indexes" << std::endl;
			exit(1);
		}
	}

	virtual std::vector<std::string> getPath(State<Point>* state) const {
		std::vector<std::string> path;
		State<Point>* parent, *current = state;
		while ((parent = current->getParent()) != nullptr) {
			if (parent->getValue().getX() < current->getValue().getX())
				path.insert(path.begin(), "down");
			else if (parent->getValue().getX() > current->getValue().getX())
				path.insert(path.begin(), "up");
			else if (parent->getValue().getY() < current->getValue().getY())
				path.insert(path.begin(), "right");
			else if (parent->getValue().getY() > current->getValue().getY())
				path.insert(path.begin(), "left");
			current = parent;
		}
		return path;
	}

	virtual double getPathCost(State<Point>* state) const {
		double cost = 0;
		const State<Point>* current = state;
		do {
			cost += current->getCost();
		} while ((current = current->getParent()) != nullptr);
		return cost;
	}

	virtual double getEstimatedCostToEnd(State<Point>* state) const {
		Point p1 = state->getValue();
		Point p2 = _goalState->getValue();
		double x1 = p1.getX(), x2 = p2.getX();
		double y1 = p1.getY(), y2 = p2.getY();
		return (std::abs(x1 - x2) + std::abs(y1 - y2));
	}

	virtual std::vector<State<Point>*> getNeighbors(State<Point>* state) const {
		int x = state->getValue().getX();
		int y = state->getValue().getY();
		std::vector<State<Point>*> neighbors;
		auto thisRow = _cells.begin() + x;
		if (y > 0)
			neighbors.push_back(thisRow->operator[](y - 1));
		if (y < _cols - 1)
			neighbors.push_back(thisRow->operator[](y + 1));
		if (x > 0) {
			auto upperRow = _cells.begin() + x - 1;
			neighbors.push_back(upperRow->operator[](y));
		}
		if (x < _rows - 1) {
			auto lowerRow = _cells.begin() + x + 1;
			neighbors.push_back(lowerRow->operator[](y));
		}
		return neighbors;
	}

	std::string toString() const {
		std::string stringFormat = "";
		for (std::vector<State<Point>*> row : _cells) {
			for (State<Point>* cell : row)
				stringFormat += std::to_string(cell->getCost()) + ",";
			stringFormat.erase(--stringFormat.end());
			stringFormat += "\n";
		}
		stringFormat += _initialState->getValue().toString();
		stringFormat += "\n";
		stringFormat += _goalState->getValue().toString();
		return stringFormat;
	}

	~SearchableMatrix() {
		for (std::vector<State<Point>*> row : _cells) {
			for (State<Point>* cell : row)
				delete cell;
		}
	}
};

#endif
