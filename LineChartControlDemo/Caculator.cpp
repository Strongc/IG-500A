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
	// ����DDQ�� ������ʽ
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

	//��ȡ�����µĽ��ٶȺ����ǻ���whileѭ���е��ô˵ݹ麯��
	void cacloop(){
		//Ϊʲô��loop�����ڲ�����I�أ� ��Ϊ������ⲿ�Ļ���ÿ�θ���Iֵ��I�Ͳ��������I��
		// ���ڲ�����Ļ���ÿ��loop�����Զ�����
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
		
		//����H����
		float H[4][4] = {
			{ 0, -1 * ddQ.ddqx, -1 * ddQ.ddqy, -1 * ddQ.ddqz },
			{ ddQ.ddqx, 0, ddQ.ddqz, -1 * ddQ.ddqy },
			{ ddQ.ddqy, ddQ.ddqz, 0, ddQ.ddqx },
			{ ddQ.ddqz, ddQ.ddqy, -1 *ddQ.ddqx, 0},
		};

		// ��4x4����ǿתΪ��άָ�룬maybe some problem
		kMatrix((float**)I, 4, 4, temp4);
		kMatrix((float **)H, 4, 4, temp4);

		// �����ά����, ����ʽ�еĵ�һ��4x4����
		float first[4][4];
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				first[i][j] = I[i][j] + H[i][j];
			}
		}

		float tempResult[4][4];
		memcpy(tempResult, result, sizeof(float)* 16);

		//ǿתagain, I am sorry
		cacMatrix((float**)first, (float**)tempResult, 4, 1, (float**)result);

		return;
	}

public:
	//���θı�
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