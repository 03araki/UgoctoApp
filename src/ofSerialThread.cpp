#include "ofSerialThread.h"

ofSerialThread::ofSerialThread()
{
	bSwitch = false;
	iEncCount = 0;
	iXAcc = 0;
	iYAcc = 0;
	iZAcc = 0;
}

bool ofSerialThread::start(int deviceNumber)
{
	if (!serial.setup(deviceNumber, 230400)) return false;

	serial.flush();
	startThread();
	return true;
}

void ofSerialThread::stop()
{
	stopThread();
	serial.close();
}

void ofSerialThread::threadedFunction()
{
	char RxBuf[256];		// recieved serial data
	char DataStr[256];
	char cData[9];
	int iDataIndex;

	cData[8] = '\0';

	while (isThreadRunning()) {
		if (serial.available()) {
			int iResult = serial.readBytes(RxBuf, 256);
			RxBuf[iResult] = '\0';
			if (iResult == 35) {
				// get switch data
				if (RxBuf[0] == '1') bSwitch = false;
				else bSwitch = true;
				// get encoder data
				for (int k = 0; k < 8; k++) cData[k] = RxBuf[1 + k];
				sscanf(cData, "%x", &iEncCount);
				// get acc sensor x-axis data
				for (int k = 0; k < 8; k++) cData[k] = RxBuf[9 + k];
				sscanf(cData, "%x", &iXAcc);
				// get acc sensor y-axis data
				for (int k = 0; k < 8; k++) cData[k] = RxBuf[17 + k];
				sscanf(cData, "%x", &iYAcc);
				// get acc sensor z-axis data
				for (int k = 0; k < 8; k++) cData[k] = RxBuf[25 + k];
				sscanf(cData, "%x", &iZAcc);
			}
		}
	}
}