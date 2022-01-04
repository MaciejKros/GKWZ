#pragma once
#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

#include <math.h>
#include <vector>

class Matrix {
public:
	vector<vector<double>> matr44;

	Matrix() {
	}

	Matrix(vector<vector<double>> matr) {
		this->matr44 = matr;
	}

	vector<vector<double>> getUnitMatrix() {
		vector<vector<double>> matr(4, vector<double>(4, 0));
		int i;
		for (i = 0; i < 4; i++)
			matr[i][i] = 1;
		return matr;
	}

	vector<vector<double>> getProjectionMatrix(double d) {
		vector<vector<double>> matr(4, vector<double>(4, 0));
		int i;
		for (i = 0; i < 3; i++)
			matr[i][i] = 1;
		matr[3][2] = (double)1 / d;
		//            {1, 0, 0, 0}
		//            {0, 1, 0, 0}
		//            {0, 0, 1, 0}
		//            {0, 0, 1 / d, 0}
		return matr;
	}

	vector<vector<double>> getTranslationMatrix(double Tx, double Ty, double Tz) {
		vector<vector<double>> matr(4, vector<double>(4, 0));
		int i;
		for (i = 0; i < 4; i++)
			matr[i][i] = 1;
		matr[0][3] = Tx;
		matr[1][3] = Ty;
		matr[2][3] = Tz;
		/*
					{1, 0, 0, Tx}
					{0, 1, 0, Ty}
					{0, 0, 1, Tz}
					{0, 0, 0, 1}
		*/
		return matr;
	}

	vector<vector<double>> getOXRotationMatrix(double fi) {
		vector<vector<double>> matr(4, vector<double>(4, 0));
		matr[0][0] = 1;
		matr[3][3] = 1;
		matr[1][1] = cos(fi);
		matr[1][2] = -sin(fi);
		matr[2][1] = sin(fi);
		matr[2][2] = cos(fi);
		/*
					{1, 0, 0, 0}
					{0, cos(fi), -sin(fi), 0}
					{0, sin(fi), cos(fi), 0}
					{0, 0, 0, 1}
		*/
		return matr;
	}

	vector<vector<double>> getOYRotationMatrix(double fi) {
		vector<vector<double>> matr(4, vector<double>(4, 0));
		matr[0][0] = cos(fi);
		matr[0][2] = sin(fi);
		matr[1][1] = 1;
		matr[2][0] = -sin(fi);
		matr[2][2] = cos(fi);
		matr[3][3] = 1;
		/*
					{cos(fi), 0, sin(fi), 0}
					{0, 1, 0, 0}
					{-sin(fi), 0, cos(fi), 0}
					{0, 0, 0, 1}
		*/
		return matr;
	}

	
	vector<vector<double>> getOZRotationMatrix(double fi) {
		vector<vector<double>> matr(4,vector<double>(4,0));
        matr[0][0]=cos(fi);
        matr[0][1]=-sin(fi);
        matr[1][0]=sin(fi);
        matr[1][1]=cos(fi);
        matr[2][2]=1;
        matr[3][3]=1;
/*
            {cos(fi), -sin(fi), 0, 0}
            {sin(fi), cos(fi), 0, 0}
            {0, 0, 1, 0}
            {0, 0, 0, 1}
*/
        return matr;
    }

	vector<vector<double>> multiplyMatrixes(vector<vector<double>> a, vector<vector<double>> b) {
        int aRows = a.size(),
                aCols = a[0].size(),
                bRows = b.size(),
                bCols = b[0].size();

        if (aCols != bRows) {
            throw "A:Rows did not match B:Cols.";
        }

		vector<vector<double>> resultMatrix (aRows, vector<double>(bCols,0));

        for (int i = 0; i < aRows; i++) { // aRow
            for (int j = 0; j < bCols; j++) { // bCol
                for (int k = 0; k < aCols; k++) { // aCol
                    resultMatrix[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return resultMatrix;
    } 
};



#endif /*MATRIX_H*/