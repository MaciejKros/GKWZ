#pragma once
#ifndef POINT2D_H
#define POINT2D_H

class Point2d {
public:
	double x;
	double y;
	double w;

	Point2d() {
	}

	Point2d(double x, double y, double w) {
		this->x = x;
		this->y = y;
		this->w = w;
	}

	void normalize2dPoint() {
		this->x = this->x / this->w;
		this->y = this->y / this->w;
		this->w = this->w / this->w;
	}

	string toString() {
		return "x=" + to_string(this->x) + " "
			+ "y=" + to_string(this->y) + " "
			+ "w=" + to_string(this->w) + "\n";
	}
};


#endif /*POINT2D_H*/