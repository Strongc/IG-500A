/*
����������㺯��
*/
#pragma once
#include <iostream>
using namespace std;

// ���Ͼ���˷�̫������[ʹ��ģ�壬Ϊ���������������˴���]
// ����ĳ˷�������������λ���飬n�����һ������Ϊn�У�m����second����m��
//void cacMatrix(float **first, float **second, const int n, const int m, const int nm, float **result);

//matrix in and out
//����˷���ÿ��Ԫ�ض�����k
//void kMatrix(float **matrix, int n, int m, float k);

class Matrix
{
public:
	Matrix();
	Matrix(int mm, int nn);
	Matrix(const Matrix &src);

	~Matrix();

	Matrix& operator=(const Matrix &src);//����"="�����
	Matrix operator * (const Matrix &m2); //����˷�
	void display();
	void input();
	void setInit(int mm, int nn);
	double **data;
	double ** getData(){
		return data;
	}
private:
	int m, n;//���������������
};//�ඨ�����

