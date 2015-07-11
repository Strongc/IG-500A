#include <stdio.h>
#include "MyMatrix.h"
#include <string.h>
#include <cmath>

struct  State
{
	float fi;
	float th;
	float arf;
};

struct AngleSpeed{
	float wx;
	float wy;
	float wz;
};

struct DDQ{
	float ddqx;
	float ddqy;
	float ddqz;
};

class Caculator {
private:
	float t;
	State state;
	DDQ ddQ;
	AngleSpeed angleSpeed;
	// 计算DDQ， 出参形式
	void cacDDQ(const AngleSpeed *angleSpeed, DDQ *ddQ){
		ddQ->ddqx = angleSpeed->wx * t;
		ddQ->ddqy = angleSpeed->wy * t;
		ddQ->ddqz = angleSpeed->wz * t;
		return;
	}

	inline float MyPow(float a, float b, float c){
		return a*a + b*b + c*c;
	}

	float result[4][1] = {
		{ 1 },
		{ 0 },
		{ 0 },
		{ 0 }
	};

	//获取到了新的角速度后，我们会在while循环中调用此递归函数
	void cacloop(){
		//为什么在loop函数内部定义I呢， 因为如果在外部的话，每次更改I值，I就不是意义的I了
		// 在内部定义的话，每次loop都会自定更新
		float I[4][4] = {
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
		};
		float temp1[4][4];
		float temp2 = MyPow(ddQ.ddqx, ddQ.ddqy, ddQ.ddqz);
		float temp3 = 1 - temp2 / 8 + temp2*temp2 / 384;
		float temp4 = 0.5 - temp2 / 48;
		
		//定义H矩阵
		float H[4][4] = {
			{ 0, -1 * ddQ.ddqx, -1 * ddQ.ddqy, -1 * ddQ.ddqz },
			{ ddQ.ddqx, 0, ddQ.ddqz, -1 * ddQ.ddqy },
			{ ddQ.ddqy, ddQ.ddqz, 0, ddQ.ddqx },
			{ ddQ.ddqz, ddQ.ddqy, -1 *ddQ.ddqx, 0},
		};

		// 把4x4数组强转为二维指针，maybe some problem
		kMatrix((float**)I, 4, 4, temp4);
		kMatrix((float **)H, 4, 4, temp4);

		// 定义二维数组, 即公式中的第一个4x4矩阵
		float first[4][4];
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				first[i][j] = I[i][j] + H[i][j];
			}
		}

		float tempResult[4][4];
		memcpy(tempResult, result, sizeof(float)* 16);

		//强转again, I am sorry
		cacMatrix((float**)first, (float**)tempResult, 4, 1, (float**)result);

		return;
	}

public:
	//出参改变
	void getState(State *state){
		float temp1 = 2 * (result[0][0] * result[1][0] + result[1][0] * result[2][0]);
		float temp2 = 1 - 2 * (result[1][0] * result[1][0] + result[2][0] * result[2][0]);
		state->arf = atan2(temp1, temp2);
		float temp3 = 2 * (result[0][0] * result[2][0] - result[1][0] * result[3][0]);
		state->fi = asin(temp3);
		float temp4 = 2 * (result[0][0] * result[3][0] - result[1][0] * result[2][0]);
		float temp5 = 1 -  2 * (result[2][0] * result[2][0] - result[3][0] * result[3][0]);
		state->th = atan2(temp4, temp5);
		
		return;
	}
};