#include "stdafx.h"
#include "ig500.h"

// 矩阵的乘法，输入两个二位数组，n代表第一个矩阵为n行，m代表second具有m列
// nm参数为 first矩阵列数 == second矩阵行数 == nm
//void cacMatrix(float **firstpointer, float **secondpointer, const int n, const int m, const int nm, float **resultpointer){
//
//	float(*first)[nm] = (float(*)[nm])firstpointer;
//	float(*second)[m] = (float(*)[m])secondpointer;
//	float(*result)[m] = (float(*)[m])resultpointer;
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < m; j++){
//			for (int k = 0; k<n; ++k){
//				result[i][j] += first[i][k] * second[k][j];
//			}
//		}
//	}
//
//	return;
//}

//matrix in and out
//矩阵乘法，每个元素都乘以k
//void kMatrix(float **matrixpointer, int n, int m, float k){
//	float(*matrix)[3] = (float(*)[3])matrixpointer;
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < m; j++){
//			matrix[i][j] *= k;
//		}
//	}
//	return;
//}

/*
DCM=
cos2cos3 sin1sin2cos3−cos1sin3 cos1sin2sin3+sin1sin3
cos2sin3 sin1sin2sin3+cos1cos3 cos1sin2sin3−sin1cos3
−sin2    sin1cos2              cos1cos2
*/
void getDCM(Euler *state, Matrix &dcm){

	// dcm更改可以直接作用于dcmpointer
	(dcm.data)[0][0] = cos(state->pitch) * cos(state->yaw);
	dcm.data[0][1] = sin(state->roll) * sin(state->pitch) * cos(state->yaw) - cos(state->roll) * sin(state->yaw);
	dcm.data[0][2] = cos(state->roll) * sin(state->pitch) * sin(state->yaw) + sin(state->roll) * sin(state->yaw);

	dcm.data[1][0] = cos(state->pitch) * sin(state->yaw);
	dcm.data[1][1] = sin(state->roll) * sin(state->pitch) * sin(state->yaw) + cos(state->roll) * cos(state->yaw);
	dcm.data[0][2] = cos(state->roll) * sin(state->pitch) * sin(state->yaw) - sin(state->roll) * cos(state->yaw);

	dcm.data[2][0] = -sin(state->pitch);
	dcm.data[2][1] = sin(state->roll) * cos(state->pitch);
	dcm.data[2][2] = cos(state->roll) * cos(state->pitch);

	return;
}

void IG::setUp(){
	SbgOutput output;
	if (sbgComInit("COM3", 115200, &protocolHandle) == SBG_NO_ERROR) {
		// Wait until the device has been initialised
		sbgSleep(100);

		while (1) {
			// Ask euler angles and position to the device
			// TODO 现在这样写有点硬耦合
			// 1. 把获取数据封装成一个函数，那样以后替换算法会好点
			error = sbgGetSpecificOutput(protocolHandle, SBG_OUTPUT_EULER, &output);
			error = sbgGetSpecificOutput(protocolHandle, SBG_OUTPUT_ACCELEROMETERS, &output);
			if (error == SBG_NO_ERROR)
			{
				tempStore(&output); //把output数据更新到类field域中
				loop();  //循环计算
			} else {
				printf("error when get euler or position data from IG-500A\n");
			}

			// Small pause to unload CPU
			// 周期为0.1s
			sbgSleep(100);
		}
		return;
	} else {
		fprintf(stderr, "Unable to open IG-500 device\n");
		return;
	}

	return;
}

void IG::tempStore(const SbgOutput *output){
	// Euler
	fXAngle = output->stateEuler[0];
	fYAngle = output->stateEuler[1];
	fZAngle = output->stateEuler[2];

	// Accelerate
	fXAcce = output->stateEuler[0];
	fYAcce = output->stateEuler[1];
	fZAcce = output->stateEuler[2];

	return;
}

void IG::loop(){
	euler.roll = fXAngle;
	euler.pitch = fYAngle;
	euler.yaw = fZAngle;

	getDCM(&euler, dcm);  //获取dcm矩阵

	SensorSpeed.data[0][0] += 0.1 *fXAcce;  //根据加速度，累计速度，不追求精确
	SensorSpeed.data[1][0] += 0.1 *fYAcce;
	SensorSpeed.data[2][0] += 0.1 *fZAcce;

	//根据DCM进行变换,进行矩阵乘法
	//cacMatrix((float **)dcm, (float **)SensorSpeed, 3, 1, 3,(float **)EarthSpeed);
	EarthSpeed = dcm * SensorSpeed;

	//根据EarthSpeed，计算出地球位移
	fXPosition += EarthSpeed.data[0][0] * 0.1;
	fYPosition += EarthSpeed.data[0][1] * 0.1;
	fZPosition += EarthSpeed.data[0][2] * 0.1;

	return;
}