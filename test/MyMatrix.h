/*
定义矩阵运算函数
*/
#pragma once
#include <iostream>
using namespace std;

// 网上矩阵乘法太过复杂[使用模板，为了适配而大大增加了代码]
// 矩阵的乘法，输入两个二位数组，n代表第一个矩阵为n行，m代表second具有m列
//void cacMatrix(float **first, float **second, const int n, const int m, const int nm, float **result);

//matrix in and out
//矩阵乘法，每个元素都乘以k
//void kMatrix(float **matrix, int n, int m, float k);

class Matrix
{
public:
	Matrix();
	Matrix(int mm, int nn);
	Matrix(const Matrix &src);

	~Matrix();

	Matrix& operator=(const Matrix &src);//重载"="运算符
	Matrix operator * (const Matrix &m2); //矩阵乘法
	void display();
	void input();
	void setInit(int mm, int nn);
	double **data;
	double ** getData(){
		return data;
	}
private:
	int m, n;//矩阵的行数，列数
};//类定义结束

