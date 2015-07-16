#include "MyMatrix.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int main(){

    Matrix matrix1(3, 3);
    Matrix matrix2(3, 1);
    matrix1.data[0][0] = 1;
    matrix1.data[0][1] = 0;
    matrix1.data[0][2] = 1;
    matrix1.data[1][0] = 0;
    matrix1.data[1][1] = 1;
    matrix1.data[1][2] = 2;
    matrix1.data[2][0] = 0;
    matrix1.data[2][1] = 0;
    matrix1.data[2][2] = 1;

    matrix2.data[0][0] = 2;
    matrix2.data[1][0] = 2;
    matrix2.data[2][0] = 2;

    Matrix result(3,1);
    result = matrix1 * matrix2;
    cout << result.data[0][0] << endl;  // 4
    return 0;
}