#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>

class Point {
	int _x, _y;
public:
	Point() {}
	Point(int x, int y): _x(x), _y(y) {}
	Point(std::string x, std::string y): _x(std::stod(x)), _y(std::stod(y)) {}
	
	int getX() const {
		return _x;
	}

	int getY() const {
		return _y;
	}

	bool operator==(const Point& other) const {
		return ((_x == other.getX()) && (_y == other.getY()));
	}

	std::string toString() {
		return std::to_string(_x) + ", " + std::to_string(_y);
	}
};

#endif