/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "oDrive.h"

#include <string>
#include <unistd.h>
#define	ERROR_COMMAND "ERROR could not write command"



oDrive::oDrive() {
	// TODO Auto-generated constructor stub

}

oDrive::oDrive(std::string portName){
	m_oDrivePort = new port(portName);
}
int oDrive::commandConsole(){
    std::string out;
        std::cout << "********************************" << std::endl;
        std::cout << "| oDrive Tool on Toradex       |" << std::endl;
        std::cout << "| Please input ASCII comands   |" << std::endl;
        std::cout << "| To control oDrive            |" << std::endl;
        std::cout << "********************************" << std::endl;

		//oDrive->writeToPort("w axis0.requested_state 3");
        std::string input="aaaa";
		char startLetter= 'a';
		while(1){
            std::cout<<">>";
            getline(std::cin, input);
			startLetter = input[0];
			if(input=="quit"){
				break;
			}

			switch (startLetter) {
				case 'r':
					m_oDrivePort->writeToPort(input);
					usleep(100);
					out = m_oDrivePort->readFromPort();
                    std::cout << out << std::endl;
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
    std::string command = "w axis"+ std::to_string(axis)+ ".requested_state "+std::to_string(state);
	m_oDrivePort->writeToPort(command);
	usleep(100);
	return EXIT_SUCCESS;
}
int oDrive::setLockinVelocity(int axis, float vel){
    std::string command = "w axis"+std::to_string(axis)+".config.general_lockin.vel "+std::to_string(vel);
	m_oDrivePort->writeToPort(command);
	usleep(100);
	return EXIT_SUCCESS;
}
int oDrive::getLockinVelocity(int axis){
    std::string command = "r axis"+std::to_string(axis)+".config.general_lockin.vel";
    std::string out;
	m_oDrivePort->writeToPort(command);
	usleep(100);
	out = m_oDrivePort->readFromPort();
    std::cout << out << std::endl;
	return EXIT_SUCCESS;
}

float oDrive::getPosInTurns(int axis){
    std::string command = "f "+std::to_string(axis);
    std::string out;
    std::string delimiter = " ";
	float pos;
	if(m_oDrivePort->writeToPort(command)<0){
        std::cout<<ERROR_COMMAND<<std::endl;
    return 0;
	}
	usleep(100);
	out = m_oDrivePort->readFromPort();
	pos =stof(out.substr(0,out.find(delimiter)));
	return pos;
}
int oDrive::setPosInTurns(int axis,float pos){
    std::string command = "q "+std::to_string(axis)+" "+std::to_string(pos);
    std::string out;
    std::string delimiter = " ";
	if(m_oDrivePort->writeToPort(command)<0){
        std::cout<<ERROR_COMMAND<<std::endl;
        return 0;
	}
	usleep(100);
	return EXIT_SUCCESS;
}
oDrive::~oDrive() {
	delete m_oDrivePort;
	// TODO Auto-generated destructor stub
}

