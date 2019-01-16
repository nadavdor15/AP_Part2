#ifndef SEARCHABLE_MATRIX_H
#define SEARCHABLE_MATRIX_H 

#include "Searchable.h"
#include "StringHelper.h"
#include "Point.h"
#include <string>
#include <vector>

#include <iostream>

class SearchableMatrix : public Searchable<Point> {
	std::vector<std::vector<double>> _cellsVector;
	std::vector<std::vector<State<Point>*>> _pointsVector;
	int _rows, _cols;
public:
	SearchableMatrix(const std::string str) {
		std::vector<std::string> rows = StringHelper::split(str, "\n");
		std::vector<std::string> startPoint = StringHelper::split(rows.front(), ",");
		rows.erase(--rows.end());
		std::vector<std::string> endPoint = StringHelper::split(rows.front(), ",");
		rows.erase(--rows.end());
		_initialState = new State<Point>(Point(startPoint[0], startPoint[1]));
		_goalState = new State<Point>(Point(endPoint[0], endPoint[1]));
		std::vector<std::vector<std::string>> cells;
		for (std::string s : rows) {
			std::vector<std::string> singleRow = StringHelper::split(s, ",");
			cells.push_back(singleRow);
		}
		int i = 0, j = 0;
		for (std::vector<std::string> vec : cells) {
			std::vector<double> row;
			std::vector<State<Point>*> pointsRow;
			for (std::string s : vec) {
				row.push_back(std::stod(s));
				State<Point>* state = new State<Point>(Point(i, j));
				state->setCost(std::stod(s));
				pointsRow.push_back(state);
				j++;
			}
			_cellsVector.push_back(row);
			_pointsVector.push_back(pointsRow);
			i++;
		}
		_rows = rows.size();
		_cols = rows[0].size();
	}

	std::string toString() {
		std::string stringFormat = "";
		for (std::vector<double> vec : _cellsVector) {
			for (double cell : vec)
				stringFormat += std::to_string(cell) + ",";
			stringFormat.erase(--stringFormat.end());
			stringFormat += "\n";
		}
		stringFormat.erase(--stringFormat.end());
		return stringFormat;
	}

	virtual std::vector<std::string> getPath(State<Point>* end) {
		std::vector<std::string> path;
		State<Point>* parent, *current = end;
		while ((parent = current->getParent()) != nullptr) {
			if (parent->getValue().getX() < current->getValue().getX())
				path.push_back("right");
			else if (parent->getValue().getX() > current->getValue().getX())
				path.push_back("left");
			if (parent->getValue().getY() < current->getValue().getY())
				path.push_back("down");
			else if (parent->getValue().getY() > current->getValue().getY())
				path.push_back("up");
			current = parent;
		}
		return path;
	}

	virtual std::vector<State<Point>*> getNeighbors(State<Point>* state) {
		int x = state->getValue().getX();
		int y = state->getValue().getY();
		std::vector<State<Point>*> a;
		if (y > 0) {
			auto upperRow = _pointsVector.begin() + y - 1;
			if (x > 0)
				a.push_back(upperRow->operator[](x - 1));
			if (x < _cols - 1)
				a.push_back(upperRow->operator[](x + 1));
		}
		if (y < _rows - 1) {
			auto lowerRow = _pointsVector.begin() + y + 1;
			if (x > 0)
				a.push_back(lowerRow->operator[](x - 1));
			if (x < _cols - 1)
				a.push_back(lowerRow->operator[](x + 1));
		}
		return a;
	}

	~SearchableMatrix() {
		if (_initialState != nullptr)
			delete _initialState;
		if (_goalState != nullptr)
			delete _goalState;
	}
};

#endif