#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Scene.h"
#include "Point2d.h"
#include <math.h>
#include <algorithm>
#include "Line.h"
#include <limits>
#include <SDL.h>

using namespace std;

class Camera {
public:
	Scene scene;
	double x_min = -1;
	double x_max = 1;
	double y_min = -1;
	double y_max = 1;
	int height = 650;
	int width = 650;
	vector<Uint32> buffer;

	Camera() {
	}

	Camera(int width, int height) {
		this->height = height;
		this->width = width;
		vector<Uint32> temp(height * width, 0xffffffff);
		this->buffer = temp;
	}

	Camera(Scene scene, int width, int height) {
		this->scene = scene;
		this->height = height;
		this->width = width;
		vector<Uint32> temp(height * width, 0xffffffff);
		this->buffer = temp;
	}

	bool point2dOnCamera(Point2d p) {
		return p.x >= x_min && p.x <= x_max && p.y >= y_min && p.y <= y_max;
	}

	bool triangleOnCamera(Triangle t) {
		return point2dOnCamera(t.points2d[0]) && point2dOnCamera(t.points2d[1]) && point2dOnCamera(t.points2d[2]);
	}

	vector<int> point2dToCoordinates(double x, double y) {
		vector<int> coords;
		coords.push_back(round((x - x_min) * this->width / (x_max - x_min)));
		coords.push_back(this->height - (round((y - y_min) * this->height / (y_max - y_min))));
		return coords;
	}
	/*
    vector<Triangle> trianglesOnCamera() {
		vector<Triangle> camTriangles;
        for(Triangle t : this->scene.visibleTriangleList)
			if (triangleOnCamera(t))
				camTriangles.push_back(t);
        return camTriangles;
    }
	*/
	void setTrianglesOnCamera() {
		vector<Triangle> camTriangles;
		for (Triangle t : this->scene.visibleTriangleList)
			if (triangleOnCamera(t))
				camTriangles.push_back(t);
		this->scene.visibleTriangleList = camTriangles;
	}
	/*
	vector<Triangle> trianglesBufferCoordinates() {
		vector<Triangle> tBC;

		for (Triangle t : this->scene.visibleTriangleList) {
			for (int i = 0; i < 3; i++) {
				t.bufferCoordinates.push_back(point2dToCoordinates(t.points2d[i].x, t.points2d[i].y));
			}
			tBC.push_back(t);
		}
		return tBC;
	}
	*/
	void setTrianglesBufferCoordinates() {
		vector<Triangle> tBC;

		for (Triangle t : this->scene.visibleTriangleList) {
			for (int i = 0; i < 3; i++) {
				t.bufferCoordinates.push_back(point2dToCoordinates(t.points2d[i].x, t.points2d[i].y));
			}
			tBC.push_back(t);
		}
		this->scene.visibleTriangleList = tBC;
	}

	inline void paintCoordinates(int x, int y, Uint32 color) {
		Uint32* point = this->buffer.data();
		Uint32* temp = point + y * this->height + x;
		*temp = color;
	}
	/*
	void paintEdge(int x1, int y1, int x2, int y2, Uint32 color) {
		if (y1 == y2) {
			if (x1 > x2)
				for (int i = x2; i <= x1; i++)
					paintCoordinates(i, y1, color);
			else
				for (int i = x1; i <= x2; i++)
					paintCoordinates(i, y1, color);
		}
		else if (y1 > y2) {
				for (int i = y2; i <= y1; i++) {
					if (x1 != x2) {
						int x = round((double)((i * x1 - i * x2 - y2 * x1 + y1 * x2) / (y1 - y2)));
						paintCoordinates(x, i, color);
					}
					else {
						paintCoordinates(x1, i, color);
					}
				}
		}
		else {
			for (int i = y1; i <= y2; i++) {
				if (x1 != x2) {
					int x = round((double)((i * x1 - i * x2 - y2 * x1 + y1 * x2) / (y1 - y2)));
					paintCoordinates(x, i, color);
				}
				else {
					paintCoordinates(x1, i, color);
				}
			}
		}
	}
	*/
	void paintLine(int y, int x_left, int x_right, Uint32 color) {
		if (x_left <= x_right) {
			for (int i = x_left; i <= x_right; i++)
				paintCoordinates(i, y, color);
		}
	}

	int getIntersectionX(double y, double x1, double x2, double y1, double y2) {
		return round(y*(x1-x2)-y2*x1+y1*x2)/(y1-y2);
	}

	void paintScanLines() {
		fill(this->buffer.begin(), this->buffer.end(), 0xffffffff);
		vector<Line> scanLines;
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->scene.visibleTriangleList.size(); j++) {
				Triangle* t;
				t = &this->scene.visibleTriangleList[j];
				if (i== t->bufferCoordinates[0][1] && i == t->bufferCoordinates[1][1]) {
					Line l(i, t->bufferCoordinates[0][0], t->bufferCoordinates[1][0], t);
					scanLines.push_back(l);
				}
				else if (i == t->bufferCoordinates[1][1] && i == t->bufferCoordinates[2][1]) {
					Line l(i, t->bufferCoordinates[1][0], t->bufferCoordinates[2][0], t);
					scanLines.push_back(l);
				}
				else if (i == t->bufferCoordinates[0][1] && i == t->bufferCoordinates[2][1]) {
					Line l(i, t->bufferCoordinates[0][0], t->bufferCoordinates[2][0], t);
					scanLines.push_back(l);
				}
				else if (((i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[2][1]) ||
					(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[0][1])) &&
					((i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[1][1]) ||
						(i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[0][1])) &&
					((i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[2][1]) ||
						(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[1][1]))) {
					int xL, xR;
					if (i == t->bufferCoordinates[0][1]) {
						xL = t->bufferCoordinates[0][0];
						xR = getIntersectionX((double)i, (double)t->bufferCoordinates[1][0], (double)t->bufferCoordinates[2][0],
							(double)t->bufferCoordinates[1][1], (double)t->bufferCoordinates[2][1]);
						Line l(i, xL, xR, t);
						scanLines.push_back(l);
					}
					else if (i == t->bufferCoordinates[1][1]) {
						xL = t->bufferCoordinates[1][0];
						xR = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[2][0],
							(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[2][1]);
						Line l(i, xL, xR, t);
						scanLines.push_back(l);
					}
					else {
						xL = t->bufferCoordinates[2][0];
						xR = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[1][0],
							(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[1][1]);
						Line l(i, xL, xR, t);
						scanLines.push_back(l);
					}
				}
				else if (((i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[1][1]) ||
					(i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[0][1])) &&
					((i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[2][1]) ||
						(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[1][1]))) {
					int xL, xR;
					xL = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[1][0],
						(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[1][1]);
					xR = getIntersectionX((double)i, (double)t->bufferCoordinates[1][0], (double)t->bufferCoordinates[2][0],
						(double)t->bufferCoordinates[1][1], (double)t->bufferCoordinates[2][1]);
					Line l(i, xL, xR, t);
					scanLines.push_back(l);
				}
				else if (((i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[2][1]) ||
					(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[0][1])) &&
					((i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[2][1]) ||
						(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[1][1]))) {
					int xL, xR;
					xL = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[2][0],
						(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[2][1]);
					xR = getIntersectionX((double)i, (double)t->bufferCoordinates[1][0], (double)t->bufferCoordinates[2][0],
						(double)t->bufferCoordinates[1][1], (double)t->bufferCoordinates[2][1]);
					Line l(i, xL, xR, t);
					scanLines.push_back(l);
				}
				else if (((i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[2][1]) ||
					(i >= t->bufferCoordinates[2][1] && i <= t->bufferCoordinates[0][1])) &&
					((i >= t->bufferCoordinates[1][1] && i <= t->bufferCoordinates[0][1]) ||
						(i >= t->bufferCoordinates[0][1] && i <= t->bufferCoordinates[1][1]))) {
					int xL, xR;
					xL = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[2][0],
						(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[2][1]);
					xR = getIntersectionX((double)i, (double)t->bufferCoordinates[0][0], (double)t->bufferCoordinates[1][0],
						(double)t->bufferCoordinates[0][1], (double)t->bufferCoordinates[1][1]);
					Line l(i, xL, xR, t);
					scanLines.push_back(l);
				}
			}
			if (scanLines.size() > 1) {
				int xx = 0;
				vector<double> l_d(scanLines.size());
				int min_x_l = 0;
				int max_x_r = 0;
				for (xx = 0; xx < scanLines.size(); xx++)
				{
					l_d[xx] = abs(scanLines[xx].t->points3d[0].z + scanLines[xx].t->points3d[1].z + scanLines[xx].t->points3d[2].z) / 3;
					if (scanLines[xx].x_left < min_x_l)
						min_x_l = scanLines[xx].x_left; 
					if (scanLines[xx].x_right > max_x_r)
						max_x_r = scanLines[xx].x_right;
				}
				for (xx = min_x_l; xx <= max_x_r; xx++)
				{
					double min_d = numeric_limits<double>::max();
					int c_l = -1;
					for (int i = 0; i < scanLines.size(); i++)
					{
						if (scanLines[i].x_left <= xx && xx <= scanLines[i].x_right && min_d > l_d[i])
						{
							min_d = l_d[i];
							c_l = i;
						}
					}
					if (c_l > -1)
						paintCoordinates(xx, scanLines[0].y, scanLines[c_l].t->color);
				}
			}
			else if (scanLines.size() == 1) {
				paintLine(scanLines[0].y, scanLines[0].x_left, scanLines[0].x_right, scanLines[0].t->color);
			}
			scanLines.clear();
		}
	}
	/*
	void paintTriangle(Triangle t) {
		paintEdge(t.bufferCoordinates[0][0], t.bufferCoordinates[0][1], t.bufferCoordinates[1][0], t.bufferCoordinates[1][1], t.color);
		paintEdge(t.bufferCoordinates[1][0], t.bufferCoordinates[1][1], t.bufferCoordinates[2][0], t.bufferCoordinates[2][1], t.color);
		paintEdge(t.bufferCoordinates[0][0], t.bufferCoordinates[0][1], t.bufferCoordinates[2][0], t.bufferCoordinates[2][1], t.color);
	}

	void paintVisableTriangleList() {
		fill(this->buffer.begin(), this->buffer.end(), 0xffffffff);
		for (Triangle t : this->scene.visibleTriangleList)
			paintTriangle(t);
	}
	*/
};
#endif /*CAMERA_H*/