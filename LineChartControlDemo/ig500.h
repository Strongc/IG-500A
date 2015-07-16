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

//���˸о���FinalData������plotͷ�ļ��и�����
struct FinalData{
	float Angle[3];  //��Ҫ���Ƶ�ŷ���ǣ�����̬
	float Position[3];  //��Ҫ�õ���λ�ã�������
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
	
	void setUp();  //ͨ�ų�ʼ��

	/*
	��ȡ��������ֵ��������ʽ����
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
	��output�ṹ���е������ݴ浽��field��
	*/
	void tempStore(const SbgOutput *output);

	/*
	loop��������ŷ���Ǽ���λ��
	*/
	void loop();

private:
	SbgProtocolHandle protocolHandle;
	SbgErrorCode error = SBG_NO_ERROR;
	
	FinalData calData;  //Ϊ�˻�ͼ
	Euler euler;  //Ϊ������ת��
	Matrix dcm;  //dcm����

	float fXAngle = 100, fYAngle = 100, fZAngle = 100; //��ת��
	float fXAcce = 0, fYAcce = 0, fZAcce = 0;  //���ٶ�
	float fXPosition = 200, fYPosition = 200, fZPosition = 200;

	//float SensorSpeed[3][1];
	Matrix SensorSpeed;
	//float EarthSpeed[3][1];
	Matrix EarthSpeed;
};