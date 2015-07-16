#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sbgCom.h>
#include "EulerToDisplace.h"
#include "MyMatrix.h"

/*
定义封装类，封装ig500a的获取数据和处理数据
在外界，调用函数就可以得到数据，进行绘制
*/
// FIXME 由于后来直接采用了sbgOutput结构用来存放数据，所以此结构体暂时无用
//struct UserData
//{
//	float   accelerometers[3];  /*!< Accelerometers in m/s^2. */
//	float   gyroscopes[3];      /*!< 陀螺仪数据，角速度 in m/s. */
//	uint32  triggerMask;        /*!< Store which new data we have. */
//};

//个人感觉，FinalData定义在plot头文件中更合适
struct FinalData{
	float Angle[3];  //需要绘制的欧拉角，即姿态
	float Position[3];  //需要得到的位置，东北高
};

void triggerErrorCallback(SbgProtocolHandleInt *pHandler, SbgErrorCode errorCode, void *pUsrArg);
void triggerCallback(SbgProtocolHandleInt *handler, uint32 triggerMask, SbgOutput *pOutput, void *pUsrArg);

class IG{
public:
	IG(){
		dcm.setInit(3, 3);
		SensorSpeed.setInit(3, 1);
		EarthSpeed.setInit(3, 1);

		memset(&calData, 0, sizeof(calData));
		memset(&euler, 0, sizeof(euler));
	}
	
	void setUp();  //通信初始化

	/*
	获取传感器的值，出参形式返回
	*/
	void getIGData(FinalData *data){
		data->Angle[0] = fXAngle;
		data->Angle[1] = fYAngle;
		data->Angle[2] = fZAngle;
		data->Position[0] = fXPosition;
		data->Position[1] = fYPosition;
		data->Position[2] = fZPosition;
		return;
	}

	/*
	把output结构体中的数据暂存到类field中
	*/
	void tempStore(const SbgOutput *output);

	/*
	loop函数，由欧拉角计算位移
	*/
	void loop();

private:
	SbgProtocolHandle protocolHandle;
	SbgErrorCode error = SBG_NO_ERROR;
	
	FinalData calData;  //为了绘图
	Euler euler;  //为了坐标转换
	Matrix dcm;  //dcm矩阵

	float fXAngle = 100, fYAngle = 100, fZAngle = 100; //旋转角
	float fXAcce = 0, fYAcce = 0, fZAcce = 0;  //加速度
	float fXPosition = 200, fYPosition = 200, fZPosition = 200;

	//float SensorSpeed[3][1];
	Matrix SensorSpeed;
	//float EarthSpeed[3][1];
	Matrix EarthSpeed;
};