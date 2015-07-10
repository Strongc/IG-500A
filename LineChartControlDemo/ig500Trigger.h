#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sbgCom.h>
//���庯��ָ��
typedef void(*TimerFunc)();

/*
�����װ�࣬��װig500a�Ļ�ȡ���ݺʹ�������
����磬���ú����Ϳ��Եõ����ݣ����л���
*/
// FIXME ���ں���ֱ�Ӳ�����sbgOutput�ṹ����������ݣ����Դ˽ṹ����ʱ����
//struct UserData
//{
//	float   accelerometers[3];  /*!< Accelerometers in m/s^2. */
//	float   gyroscopes[3];      /*!< ���������ݣ����ٶ� in m/s. */
//	uint32  triggerMask;        /*!< Store which new data we have. */
//};

struct FinalData{
	float Angle[3];  //��Ҫ���Ƶ�ŷ���ǣ�����̬
	float Position[3];  //��Ҫ�õ���λ�ã�������
};

void triggerErrorCallback(SbgProtocolHandleInt *pHandler, SbgErrorCode errorCode, void *pUsrArg);
void triggerCallback(SbgProtocolHandleInt *handler, uint32 triggerMask, SbgOutput *pOutput, void *pUsrArg);

class IG{
public:
	void setUp();
	//��ʱ����
	//void loop(UserData *data);
	//��ʱ��
	void startTimer(TimerFunc *);
	/*
	��ȡ��������ֵ��������ʽ����
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
	��output�ṹ���е������ݴ浽��field��
	*/
	void tempStore(const SbgOutput *output);
private:
	SbgProtocolHandle protocolHandle;
	SbgErrorCode error = SBG_NO_ERROR;
	FinalData calData;

	/*
	fXAngle: x �������ת��
	fYAngle: y �������ת��
	fZAngle: z �������ת��
	fXSpeed: x ������ٶ�
	fYSpeed: y ������ٶ�
	fZSpeed: z ������ٶ�
	*/

	float fXAngle = 100, fYAngle = 100, fZAngle = 100;
	float fXPosition = 200, fYPosition = 200, fZPosition = 200;
	
	/*float tempx[2];
	float tempy[2];
	float tempz[2];*/
};