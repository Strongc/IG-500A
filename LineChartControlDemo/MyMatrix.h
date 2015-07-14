#include <iostream>
#include "stdafx.h"

using namespace std;

// ���Ͼ���˷�̫������[ʹ��ģ�壬Ϊ���������������˴���]
// ����ĳ˷�������������λ���飬n�����һ������Ϊn�У�m����second����m��
void cacMatrix(const float **first, const float **second, const int n, const int m, float **result){
	//result Ӧ����һ�� nxm ����
	for (int i = 0; i < n; i++){
		float temp = 0;
		for (int j = 0; j < m; j++){
			temp += first[i][j] * second[j][i];
			if (j == (m - 1)){
				result[i][j] = temp;
			}
		}
	}
	return;
}

//matrix in and out
//����˷���ÿ��Ԫ�ض�����k
void kMatrix(float **matrix, int n, int m, float k){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			matrix[i][j] *= k;
		}
	}
	return;
}

