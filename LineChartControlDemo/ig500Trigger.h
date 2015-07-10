#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sbgCom.h>
//定义函数指针
typedef void(*TimerFunc)();

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

struct FinalData{
	float Angle[3];  //需要绘制的欧拉角，即姿态
	float Position[3];  //需要得到的位置，东北高
};

void triggerErrorCallback(SbgProtocolHandleInt *pHandler, SbgErrorCode errorCode, void *pUsrArg);
void triggerCallback(SbgProtocolHandleInt *handler, uint32 triggerMask, SbgOutput *pOutput, void *pUsrArg);

class IG{
public:
	void setUp();
	//定时函数
	//void loop(UserData *data);
	//起定时器
	void startTimer(TimerFunc *);
	/*
	获取传感器的值，出参形式返回
	*/
	void getData(FinalData *data){
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
private:
	SbgProtocolHandle protocolHandle;
	SbgErrorCode error = SBG_NO_ERROR;
	FinalData calData;

	/*
	fXAngle: x 方向的旋转角
	fYAngle: y 方向的旋转角
	fZAngle: z 方向的旋转角
	fXSpeed: x 方向的速度
	fYSpeed: y 方向的速度
	fZSpeed: z 方向的速度
	*/

	float fXAngle = 100, fYAngle = 100, fZAngle = 100;
	float fXPosition = 200, fYPosition = 200, fZPosition = 200;
	
	/*float tempx[2];
	float tempy[2];
	float tempz[2];*/
};