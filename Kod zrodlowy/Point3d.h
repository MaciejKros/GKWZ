#pragma once
#ifndef POINT3D_H
#define POINT3D_H

using namespace std;
#include <vector>
#include <string>

class Point3d {
public:
	double x;
	double y;
	double z;
	double w;
	
	Point3d() {
	}

	Point3d(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1;
	}

	Point3d(double x, double y, double z, double w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Point3d(vector<vector<double>> vectorP) {
		this->x = vectorP[0][0];
		this->y = vectorP[1][0];
		this->z = vectorP[2][0];
		this->w = vectorP[3][0];
	}

	void normalize3dPoint() {
		this->x = this->x / this->w;
		this->y = this->y / this->w;
		this->z = this->z / this->w;
		this->w = this->w / this->w;
	}

	vector<vector<double>> getVectorP() {
		vector<vector<double>> vec(4, vector<double>(1, 0));
		vec[0][0] = this->x;
		vec[1][0] = this->y;
		vec[2][0] = this->z;
		vec[3][0] = this->w;
		return vec;
	}

	string toString() {
		return "x=" + to_string(this->x) + " "
			+ "y=" + to_string(this->y) + " "
			+ "z=" + to_string(this->z) + " "
			+ "w=" + to_string(this->w) + "\n";
	}	
};


#endif /*POINT2D_H*/