/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include <iostream>
#include "port.h"
#include <string>
#include <unistd.h>
#include "oDrive.h"
#include "pps.h"

using namespace std;

int main() {
/*
	string portName = "/dev/ttyACM0";
	oDrive * odrive = new oDrive(portName);
	odrive->commandConsole();
*/
	int second = 1000000;
	string ppsFile = "/sys/class/pps/pps0/assert";
	pps * ppsOut = new pps(ppsFile);
	string portName = "/dev/ttyACM0";
	oDrive * odrive = new oDrive(portName);
	//cout<<"Pos = "<<fixed<<odrive->getPosInTurns(0)<<endl;
	/*float pos= odrive->getPosInTurns(0);
	cout<<"Pos"<<fixed<<pos<<endl;
	usleep(second*2);
	odrive->setState(0,odrive->AXIS_STATE_CLOSED_LOOP_CONTROL);

	usleep(second*2);
	odrive->setPosInTurns(0,-1*pos);
	usleep(second*2);
	pos= odrive->getPosInTurns(0);
	cout<<"Pos"<<fixed<<pos<<endl;
	usleep(second*2);*/
    /*float pos;
	odrive->setState(0,odrive->AXIS_STATE_FULL_CALIBRATION_SEQUENCE);
	usleep(second*10);
	cout<<"Encoder Offset calibration"<<endl;
	odrive->setState(0,odrive->AXIS_STATE_ENCODER_OFFSET_CALIBRATION);
	usleep(second*10);
	pos= odrive->getPosInTurns(0);
	cout<<"Pos"<<fixed<<pos<<endl;
	usleep(second*2);
	cout<<"Actual Lockin velocity"<<endl;
	odrive->getLockinVelocity(0);
	usleep(second);

	cout<<"Setting Lockin velocity 100"<<endl;
	odrive->setLockinVelocity(0,150);
	usleep(second);
	cout<<"Setting AXIS_STATE_LOCKIN_SPIN"<<endl;
	odrive->setState(0,odrive->AXIS_STATE_LOCKIN_SPIN);
	usleep(second*3);
	for (int i = 0; i < 20; ++i) {
		cout<<"PPS"<<i+1<<endl;
		cout<<"**********************"<<endl;
		ppsOut->getPPS();
		cout<<"|"<< ppsOut->m_actual.time<<"|"<<endl;
		cout<<"|" << ppsOut->m_actual.cnt;
		for(int j = (int)to_string(ppsOut->m_actual.cnt).length(); j<20;j++)
			cout<<" ";
		cout<<"|"<<endl;
		cout<<"**********************"<<endl;
		pos= odrive->getPosInTurns(0);
		cout<<"Pos = "<<fixed<<pos<<endl;
		usleep(second);

    }*/
    odrive->setState(0,odrive->AXIS_STATE_CLOSED_LOOP_CONTROL);
    //odrive->setVelocity(1);
    usleep(10*second);
	cout<<"Setting AXIS_STATE_LOCKIN_IDLE"<<endl;
	odrive->setState(0,odrive->AXIS_STATE_IDLE);
    return 0;
};
