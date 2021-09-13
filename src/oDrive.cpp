/*
 * oDrive.cpp
 *
 *  Created on: 16. 8. 2021
 *      Author: martinek
 */

#include "oDrive.h"

#include <string>
#include <unistd.h>
#define	ERROR_COMMAND "ERROR could not write command"

using namespace std;


oDrive::oDrive() {
	// TODO Auto-generated constructor stub

}

oDrive::oDrive(string portName){
	m_oDrivePort = new port(portName);
}
int oDrive::commandConsole(){
	string out;
		cout << "********************************" << endl;
		cout << "| oDrive Tool on Toradex       |" << endl;
		cout << "| Please input ASCII comands   |" << endl;
		cout << "| To control oDrive            |" << endl;
		cout << "********************************" << endl;

		//oDrive->writeToPort("w axis0.requested_state 3");
		string input="aaaa";
		char startLetter= 'a';
		while(1){
			cout<<">>";
			getline(cin, input);
			startLetter = input[0];
			if(input=="quit"){
				break;
			}

			switch (startLetter) {
				case 'r':
					m_oDrivePort->writeToPort(input);
					usleep(100);
					out = m_oDrivePort->readFromPort();
					cout << out <<endl;
					break;
				case 'w':
					m_oDrivePort->writeToPort(input);
					usleep(100);
					break;
				default:
					m_oDrivePort->writeToPort(input);
					usleep(100);
					break;
			}
		}
		return EXIT_SUCCESS;
}
int oDrive::setState(int axis,int state){
	//TODO some checks
	string command = "w axis"+ to_string(axis)+ ".requested_state "+to_string(state);
	m_oDrivePort->writeToPort(command);
	usleep(100);
	return EXIT_SUCCESS;
}
int oDrive::setLockinVelocity(int axis, float vel){
	string command = "w axis"+to_string(axis)+".config.general_lockin.vel "+to_string(vel);
	m_oDrivePort->writeToPort(command);
	usleep(100);
	return EXIT_SUCCESS;
}
int oDrive::getLockinVelocity(int axis){
	string command = "r axis"+to_string(axis)+".config.general_lockin.vel";
	string out;
	m_oDrivePort->writeToPort(command);
	usleep(100);
	out = m_oDrivePort->readFromPort();
	cout << out <<endl;
	return EXIT_SUCCESS;
}

float oDrive::getPosInTurns(int axis){
	string command = "f "+to_string(axis);
	string out;
	string delimiter = " ";
	float pos;
	if(m_oDrivePort->writeToPort(command)<0){
		cout<<ERROR_COMMAND<<endl;
	return EXIT_FAILURE;
	}
	usleep(100);
	out = m_oDrivePort->readFromPort();
	pos =stof(out.substr(0,out.find(delimiter)));
	return pos;
}
int oDrive::setPosInTurns(int axis,float pos){
	string command = "q "+to_string(axis)+" "+to_string(pos);
	string out;
	string delimiter = " ";
	if(m_oDrivePort->writeToPort(command)<0){
		cout<<ERROR_COMMAND<<endl;
		return EXIT_FAILURE;
	}
	usleep(100);
	return EXIT_SUCCESS;
}
oDrive::~oDrive() {
	delete m_oDrivePort;
	// TODO Auto-generated destructor stub
}

