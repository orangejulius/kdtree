#ifndef POINT_H
#define POINT_H

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

class Point
{
public:
	Point() {}

	Point(double x, double y) {
		coords[0] = x;
		coords[1] = y;
	}

	double x() const {
		return coords[0];
	}

	double y() const {
		return coords[1];
	}

	double operator [](int i) {
		return coords[i];
	}

	Point operator +(const Point& p) const {
		return Point(x() + p.x(), y() + p.y());
	}

	Point operator -(const Point& p) const {
		return Point(x() - p.x(), y() - p.y());
	}

	double squaredNorm() const {
		return x()*x() + y()*y();
	}

	private:
		double coords[2];
};

ostream & operator <<(ostream& os, const Point& p) {
	os<<"x: "<<p.x()<<"y: "<<p.y()<<endl;
	return os;
}

#endif // POINT_H
