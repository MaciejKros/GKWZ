#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

using namespace std;

#include <SDL.h>
#include <vector>
#include "Point3d.h"
#include "Point2d.h"

class Triangle {
public:
	vector<Point3d> points3d;
	vector<Point2d> points2d;
	vector<vector<int>> bufferCoordinates;
	Uint32 color;
	vector<double> triangleFacingFactor;

	Triangle() {
	}

	Triangle(vector<Point3d> points3d, Uint32 color) {
		this->points3d = points3d;
		this->color = color;
		this->triangleFacingFactor.resize(4);
		this->triangleFacingFactor[0] = points3d[0].y * (points3d[1].z - points3d[2].z)
			- points3d[1].y * (points3d[0].z - points3d[2].z)
			+ points3d[2].y * (points3d[0].z- points3d[1].z);
		this->triangleFacingFactor[1] = -points3d[0].x * (points3d[1].z - points3d[2].z)
			+ points3d[1].x * (points3d[0].z - points3d[2].z)
			- points3d[2].x * (points3d[0].z - points3d[1].z);
		this->triangleFacingFactor[2] = points3d[0].x * (points3d[1].y - points3d[2].y)
			- points3d[1].x * (points3d[0].y - points3d[2].y)
			+ points3d[2].x * (points3d[0].y - points3d[1].y);
		this->triangleFacingFactor[3] = -points3d[0].x * points3d[1].y * points3d[2].z
			+ points3d[0].x * points3d[2].y * points3d[1].z
			+ points3d[1].x * points3d[0].y * points3d[2].z
			- points3d[1].x * points3d[2].y * points3d[0].z
			- points3d[2].x * points3d[0].y * points3d[1].z
			+ points3d[2].x * points3d[1].y * points3d[0].z;
	/*
	y1 * z2 - y1 * z3 - y2 * z1 + y2 * z3 + y3 * z1 - y3 * z2
	-x1 * z2 + x1 * z3 + x2 * z1 - x2 * z3 - x3 * z1 + x3 * z2
	x1 * y2 - x1 * y3 - x2 * y1 + x2 * y3 + x3 * y1 - x3 * y2
	-x1 * y2 * z3 + x1 * y3 * z2 + x2 * y1 * z3 - x2 * y3 * z1 - x3 * y1 * z2 + x3 * y2 * z1
	*/
	}

	void projectTriangleTo2d(double d) {
		//this->points2d.resize(3);
		for (int i = 0; i < 3; i++) {
			this->points2d.push_back(Point2d(this->points3d[i].x * d / this->points3d[i].z,
				this->points3d[i].y * d / this->points3d[i].z, d));
		}
	}

	void normalize2dPoints() {
		for (int i = 0; i < 3; i++)
			this->points2d[i].normalize2dPoint();
	}

	void normalize3dPoints() {
		for(int i=0; i<3; i++)
			this->points3d[i].normalize3dPoint();
	}

	string toString() {
		string triangleString= "Triangle: \n";
		for (int i = 0; i < 3; i++)
			triangleString += "points3d[" + to_string(i) + "]: " + this->points3d[i].toString();
		if(!this->points2d.empty())
			for (int i = 0; i < 3; i++)
				triangleString += "points2d[" + to_string(i) + "]: " + this->points2d[i].toString();
		if (!this->bufferCoordinates.empty())
			for (int i = 0; i < 3; i++)
				triangleString += "bufferCoordinates[" + to_string(i) + "]: "
				+ to_string(this->bufferCoordinates[i][0]) + " " + to_string(this->bufferCoordinates[i][1]) + "\n";
		triangleString += to_string(color) + "\n";
		return triangleString;
	}
};


#endif /*TRIANGLE_H*/