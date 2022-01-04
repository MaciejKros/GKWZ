#pragma once
#ifndef LINE_H
#define LINE_H

#include "Triangle.h"

class Line {
public:
	int y;
	int x_left;
	int x_right;
	Triangle* t;

	Line() {
	}

	Line(int y, int x_left, int x_right, Triangle* t) {
		this->y = y;
		if (x_left > x_right) {
			this->x_left = x_right;
			this->x_right = x_left;
		}
		else {
			this->x_left = x_left;
			this->x_right = x_right;
		}
		this->t = t;
	}
};

#endif /*LINE_H*/