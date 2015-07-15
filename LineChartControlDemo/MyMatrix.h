/*
定义矩阵运算函数
*/
#include <iostream>
#include "stdafx.h"

// 网上矩阵乘法太过复杂[使用模板，为了适配而大大增加了代码]
// 矩阵的乘法，输入两个二位数组，n代表第一个矩阵为n行，m代表second具有m列
void cacMatrix(const float **first, const float **second, const int n, const int m, float **result);

//matrix in and out
//矩阵乘法，每个元素都乘以k
void kMatrix(float **matrix, int n, int m, float k);

