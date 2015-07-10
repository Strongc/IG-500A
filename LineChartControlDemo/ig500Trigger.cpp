#include "stdafx.h"
#include "ig500Trigger.h"

//快捷注释 ctl+K 后ctl+C
//取消注释 ctl+K 后ctl+U
//void triggerErrorCallback(SbgProtocolHandleInt *pHandler, SbgErrorCode errorCode, void *pUsrArg)
//{
//	char errorMsg[256];
//
//	// Convert our error code to a human readable error message
//	sbgComErrorToString(errorCode, errorMsg);
//
//	// Display an error message
//	fprintf(stderr, "continuousErrorCallback: We have received the following error %s\n", errorMsg);
//	fflush(stderr);
//}
//
//void triggerCallback(SbgProtocolHandleInt *handler, uint32 triggerMask, SbgOutput *pOutput, void *pUsrArg)
//{
//	UserData *pUserData;
//
//	// Check if our intput arguments are valid
//	if ((pOutput) && (pUsrArg))
//	{
//		// Get our user buffer to store our received data
//		pUserData = (UserData*)pUsrArg;
//
//		// Copy our trigger mask
//		pUserData->triggerMask = triggerMask;
//
//		// Check if our output struct contains accelerometers data and if we have received new one (according to our triggers configuration)
//		if ((pOutput->outputMask&SBG_OUTPUT_ACCELEROMETERS) && (triggerMask&SBG_TRIGGER_MAIN_LOOP_DIVIDER))
//		{
//			// We have received a new accelerometers data
//			pUserData->accelerometers[0] = pOutput->accelerometers[0];
//			pUserData->accelerometers[1] = pOutput->accelerometers[1];
//			pUserData->accelerometers[2] = pOutput->accelerometers[2];
//		}
//
//		if ((pOutput->outputMask&SBG_OUTPUT_GPS_NAVIGATION) && (triggerMask&SBG_TRIGGER_GPS_VELOCITY))
//		{
//			// 除以100，得到m/s
//			/*pUserData->gyroscopes[0] = pOutput->gpsVelocity[0] / 100.0f;
//			pUserData->gyroscopes[1] = pOutput->gpsVelocity[1] / 100.0f;
//			pUserData->gyroscopes[2] = pOutput->gpsVelocity[2] / 100.0f;*/
//			pUserData->gyroscopes[0] = pOutput->gpsVelocity[0];
//			pUserData->gyroscopes[1] = pOutput->gpsVelocity[1];
//			pUserData->gyroscopes[2] = pOutput->gpsVelocity[2];
//		}
//	}
//}

void IG::setUp(){
	/*
	error = sbgComInit("COM6", 115200, &protocolHandle);
	if (error == SBG_NO_ERROR){
		error = sbgSetTriggeredMode(protocolHandle, 0, SBG_TRIGGER_MAIN_LOOP_DIVIDER, SBG_OUTPUT_ACCELEROMETERS);
		if (error == SBG_NO_ERROR){
			error = sbgSetTriggeredMode(protocolHandle, 1, SBG_TRIGGER_GPS_VELOCITY, SBG_OUTPUT_GYROSCOPES_RAW);
			if (error == SBG_NO_ERROR){
				error = sbgSetContinuousMode(protocolHandle, SBG_TRIGGERED_MODE_ENABLE, 4);
				if (error == SBG_NO_ERROR){
					// Now, we can define our trigger handlers and optionaly a error handler
					// The trigger callback function will store euler angles and velocity in the eulerVelocity list
					sbgSetContinuousErrorCallback(protocolHandle, triggerErrorCallback, NULL);
					sbgSetTriggeredModeCallback(protocolHandle, triggerCallback, &receivedData);
					// Print our header
					//printf("Acceleromters\t\t\tGPS Velocity\n");
					// Loop forever
					do
					{
						// Check for new frames received
						sbgProtocolContinuousModeHandle(protocolHandle);
						// Display values on the screen
						loop(&receivedData);
						getData(&calData);
						printf("%3.2f\t%3.2f\t%3.2f\n",	SBG_RAD_TO_DEG(calData.Angle[0]), SBG_RAD_TO_DEG(calData.Angle[1]), SBG_RAD_TO_DEG(calData.Angle[2]));
						// Unload the CPU
						sbgSleep(10);
					} while (1);
				}
				else {
					fprintf(stderr, "Could not set the trigger configuration\n");
				}

			}
			else {
				fprintf(stderr, "Could not set the trigger configuration\n");
			}
		}
		else {
			fprintf(stderr, "Could not set the trigger configuration\n");
		}

		// Close our protocol system
		sbgProtocolClose(protocolHandle);
	}
	else {
		fprintf(stderr, "Unable to open IG-500 device\n");
	}
	*/

	SbgOutput output;
	if (sbgComInit("COM3", 115200, &protocolHandle) == SBG_NO_ERROR) {
		// Wait until the device has been initialised
		sbgSleep(100);

		while (1) {
			// Ask euler angles and position to the device
			// TODO 现在这样写有点硬耦合
			// 1. 把获取数据封装成一个函数，那样以后替换算法会好点
			error = sbgGetSpecificOutput(protocolHandle, SBG_OUTPUT_EULER, &output);
			error = sbgGetSpecificOutput(protocolHandle, SBG_OUTPUT_POSITION, &output);
			//
			// Test if we were able to get valid euler angles
			//
			if (error == SBG_NO_ERROR)
			{
				/*
				// Displays sensor values in the console
				printf("%3.2f\t%3.2f\t%3.2f\n", SBG_RAD_TO_DEG(output.stateEuler[0]),
					SBG_RAD_TO_DEG(output.stateEuler[1]),
					SBG_RAD_TO_DEG(output.stateEuler[2]));
				*/

				//把output数据更新到类field域中
				tempStore(&output);
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

/*
UserData为输入数据，然后处理数据，更新fSpeed，fAngle值
函数名为loop，说明需要期定时器来每0.1秒调用

FIXME: 然而并没有什么卵用，可能以后会用到的
*/
//void IG::loop(UserData *data){
//	if (data == NULL){
//		printf("wrong data\n");
//		return;
//	}
//	/*float fXRtSpeed = data->gyroscopes[0];
//	float fYRtSpeed = data->gyroscopes[1];
//	float fZRtSpeed = data->gyroscopes[2];
//
//	float fXSpeed = data->accelerometers[0];
//	float fYSpeed = data->accelerometers[1];
//	float fZSpeed = data->accelerometers[2];*/
//
//	//0.01秒积分,虽然误差很大，但是先这样
//	/*fXAngle += (tempx[0]+tempx[1])/2*0.01; 
//	fYAngle += (tempy[0]+tempy[1])/2*0.01;
//	fZAngle += (tempz[0]+tempz[1])/2*0.01;*/
//
//	/*fXSpeed += fXSpeed*(float)0.01;
//	fYSpeed += fYSpeed*(float)0.01;
//	fZSpeed += fZSpeed*(float)0.01;*/
//
//	return;
//}

void IG::tempStore(const SbgOutput *output){
	// Euler
	fXAngle = output->stateEuler[0];
	fYAngle = output->stateEuler[1];
	fZAngle = output->stateEuler[2];
	// Position
	fXPosition = output->position[0];
	fYPosition = output->position[1];
	fZPosition = output->position[2];

	return;
}

/*
起定时器函数
*/
void IG::startTimer(TimerFunc *timerFunc){
	return;
}
