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
struct UserData
{
	float   accelerometers[3];  /*!< Accelerometers in m/s^2. */
	float   gyroscopes[3];      /*!< 陀螺仪数据，角速度 in m/s. */
	uint32  triggerMask;        /*!< Store which new data we have. */
};

struct FinalData{
	float Angle[3];  //积分得到的旋转角
	float Speed[3];  //积分得到的速度
};

void triggerErrorCallback(SbgProtocolHandleInt *pHandler, SbgErrorCode errorCode, void *pUsrArg);
void triggerCallback(SbgProtocolHandleInt *handler, uint32 triggerMask, SbgOutput *pOutput, void *pUsrArg);

class IG{
public:
	void setUp();
	//定时函数
	void loop(UserData *data);
	//起定时器
	void startTimer(TimerFunc *);
	/*
	获取传感器的值，出参形式返回
	*/
	void getData(FinalData *data){
		data->Angle[0] = fXAngle;
		data->Angle[1] = fYAngle;
		data->Angle[2] = fZAngle;
		data->Speed[0] = fXSpeed;
		data->Speed[1] = fYSpeed;
		data->Speed[2] = fZSpeed;
		return;
	}
private:
	SbgProtocolHandle protocolHandle;
	SbgErrorCode error = SBG_NO_ERROR;
	UserData receivedData;
	/*
	fXAngle: x 方向的旋转角
	fYAngle: y 方向的旋转角
	fZAngle: z 方向的旋转角
	fXSpeed: x 方向的速度
	fYSpeed: y 方向的速度
	fZSpeed: z 方向的速度
	*/
	float fXAngle = 100, fYAngle = 100, fZAngle = 100;
	float fXSpeed = 200, fYSpeed = 200, fZSpeed = 200;
};