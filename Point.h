#ifndef MATRIX_STATE_H
#define MATRIX_STATE_H

#include <string>

class Point {
	int _x, _y;
public:
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
};

// class MatrixState : public State<Point> {
// public:
// 	MatrixState(Point p): _value(p) {}
// };

#endif