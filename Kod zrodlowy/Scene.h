#pragma once
#ifndef SCENE_H
#define SCENE_H

using namespace std;

#include "Matrix.h"
#include "Triangle.h"
#include <vector>

class Scene {
public:
	vector<Triangle> triangleList;
	vector<Triangle> visibleTriangleList;
	Matrix matrix;

	Scene() {

	}

	Scene(vector<Triangle> list, Matrix mat) {
		this->matrix = mat;
		this->triangleList = list;
	}

	void multiplyMatrixAndTriangleList(){
		vector<Point3d> p3d;
		vector<Triangle> vTL;
		for (Triangle t : this->triangleList) {
			for (int i = 0; i < 3; i++)
				p3d.push_back(Point3d(matrix.multiplyMatrixes(matrix.matr44, t.points3d[i].getVectorP())));
			Triangle temp(p3d, t.color);
			temp.normalize3dPoints();
			vTL.push_back(temp);
			p3d.clear();
		}
		this->visibleTriangleList = vTL;
	}

	void projectTriangleListTo2d(double d) {
		for (int i = 0; i < this->triangleList.size(); i++)
			this->triangleList[i].projectTriangleTo2d(d);
	}

	void projectVisableTriangleListTo2d(double d) {
		for (int i = 0; i < this->visibleTriangleList.size(); i++) 
			this->visibleTriangleList[i].projectTriangleTo2d(d);
	}

	void normalizeVisableTriangleList2dPoints() {
		for (int i = 0; i < this->visibleTriangleList.size(); i++)
			this->visibleTriangleList[i].normalize2dPoints();
	}

	void normalizeVisableTriangleList3dPoints() {
		for (int i = 0; i < this->visibleTriangleList.size(); i++) 
			this->visibleTriangleList[i].normalize3dPoints();
	}

	void calculateAndSetVisableTriangleList() {
		vector<Triangle> vTL;
		double w;
		for (Triangle t : this->visibleTriangleList) {
			w = t.triangleFacingFactor[0] * t.points3d[0].x + t.triangleFacingFactor[1] * t.points3d[0].y + t.triangleFacingFactor[2] * t.points3d[0].z;
			bool rightSide=true;
			if (t.points3d[0].z < 1 || t.points3d[1].z < 1 || t.points3d[2].z < 1) {
				rightSide = false;
			}
			if (w < 0 && rightSide)
					vTL.push_back(t);
		}
		this->visibleTriangleList = vTL;
	}


	Uint32 colorDimming(Uint32 color, double factor) {
		Uint32 red= (color & 0xFF000000) * factor;
		Uint32 green = (color & 0x00FF0000) * factor;
		Uint32 blue = (color & 0x0000FF00) * factor;
		Uint32 alpha = color & 0x000000FF;

		return (red & 0xFF000000) | (green & 0x00FF0000) | (blue & 0x0000FF00) | alpha;
	}

	void createAndAddCubiod(double minX, double minY, double minZ, double maxX, double maxY, double maxZ, Uint32 color) {
		Point3d p1 (minX, minY, minZ);
		Point3d p2 (maxX, minY, minZ);
		Point3d p3 (maxX, minY, maxZ);
		Point3d p4 (minX, minY, maxZ);
		Point3d p5 (minX, maxY, minZ);
		Point3d p6 (maxX, maxY, minZ);
		Point3d p7 (maxX, maxY, maxZ);
		Point3d p8 (minX, maxY, maxZ);

		vector<Point3d> tPoints(3);
		tPoints[0] = p1;
		tPoints[1] = p2;
		tPoints[2] = p3;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color,0.9)));
		tPoints[0] = p1;
		tPoints[1] = p3;
		tPoints[2] = p4;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.9)));
		tPoints[0] = p4;
		tPoints[1] = p3;
		tPoints[2] = p7;
		this->triangleList.push_back(Triangle(tPoints, color));
		tPoints[0] = p4;
		tPoints[1] = p7;
		tPoints[2] = p8;
		this->triangleList.push_back(Triangle(tPoints, color));
		tPoints[0] = p1;
		tPoints[1] = p4;
		tPoints[2] = p8;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.8)));
		tPoints[0] = p1;
		tPoints[1] = p8;
		tPoints[2] = p5;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.8)));
		tPoints[0] = p1;
		tPoints[1] = p5;
		tPoints[2] = p6;
		this->triangleList.push_back(Triangle(tPoints, color));
		tPoints[0] = p1;
		tPoints[1] = p6;
		tPoints[2] = p2;
		this->triangleList.push_back(Triangle(tPoints, color));
		tPoints[0] = p5;
		tPoints[1] = p8;
		tPoints[2] = p7;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.9)));
		tPoints[0] = p5;
		tPoints[1] = p7;
		tPoints[2] = p6;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.9)));
		tPoints[0] = p2;
		tPoints[1] = p6;
		tPoints[2] = p7;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.8)));
		tPoints[0] = p2;
		tPoints[1] = p7;
		tPoints[2] = p3;
		this->triangleList.push_back(Triangle(tPoints, colorDimming(color, 0.8)));
	}

	void createTestScene() {
		createAndAddCubiod(-40, -10, 145, -30, 20, 150, 0x909090ff);
		createAndAddCubiod(-40, -10, 160, -30, 30, 170, 0x00ffffff);
		createAndAddCubiod(-35, -10, 125, -30, 25, 135, 0xc3c3c3ff);
		createAndAddCubiod(-35, -10, 105, -30, 15, 115, 0xffff00ff);
		createAndAddCubiod(-10, -10, 150, 0, 10, 160, 0xff00ffff);
		createAndAddCubiod(-10, -10, 130, 0, 20, 135, 0xffa500ff);
		createAndAddCubiod(-20, -10, 105, -5, 15, 115, 0xffc0cbff);
		createAndAddCubiod(10, -10, 110, 20, 20, 120, 0x00b300ff);
		createAndAddCubiod(15, -10, 125, 30, 25, 135, 0xff0000ff);
		createAndAddCubiod(10, -10, 145, 40, 15, 150, 0x0000ffff);
	}

	string toString() {
		string sceneString= "Scene:\n";
		//for (Triangle t : this->triangleList)
		//	sceneString += t.toString();
		if (!this->visibleTriangleList.empty()){
			sceneString += "Visable triangles:\n"; 
			for (Triangle t : this->visibleTriangleList)
				sceneString += t.toString();
		}
		return sceneString;
	}
};

#endif /*SCENE_H*/