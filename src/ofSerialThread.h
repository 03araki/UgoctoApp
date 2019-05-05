#pragma once

#include "ofMain.h"
#include "WinSerial.h"

class ofSerialThread : public ofThread {
public:
	CWinSerial serial;
	bool bSwitch;
	int iEncCount;
	int iXAcc, iYAcc, iZAcc;
	
	ofSerialThread();
	bool start(int deviceNumber);
	void stop();
	void threadedFunction();
};