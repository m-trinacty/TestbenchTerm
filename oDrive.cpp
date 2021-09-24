/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "oDrive.h"

#include <string>
#include <unistd.h>
#define	ERROR_COMMAND_WRITE   "ERROR could not write command"
#define	ERROR_COMMAND_READ   "ERROR could not read command"
#define INVALID_PROPERTY    "invalid property"
#define INVALID_COMMAND_FORMAT  "invalid command format"
#define UNKNOWN_COMMAND "unknown command"


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
        case 'f':
            m_oDrivePort->writeToPort(input);
            usleep(100);
            out = m_oDrivePort->readFromPort();
            std::cout << out << std::endl;
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

int oDrive::setVelocity(int axis, float vel)
{
    std::string command= "w axis"+std::to_string(axis)+".controller.input_vel " +std::to_string(vel);
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

float oDrive::getPosEstimate(int axis)
{
    std::string out;
    std::string command = "r axis"+std::to_string(axis)+".encoder.pos_estimate";
    if (m_oDrivePort->writeToPort(command)<0) {
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return EXIT_FAILURE;
    }
    usleep(100);
    out = m_oDrivePort->readFromPort();
    if (out == INVALID_PROPERTY ||out ==  INVALID_COMMAND_FORMAT ||out ==  UNKNOWN_COMMAND) {
        std::cout<<ERROR_COMMAND_READ<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout << out << std::endl;
    float pos =std::stof(out);
    return pos;
}

float oDrive::getPosEstimateCounts(int axis)
{
    std::string out;
    std::string command = "r axis"+std::to_string(axis)+".encoder.pos_estimate_counts";
    std::cout<<command<<std::endl;
    if (m_oDrivePort->writeToPort(command)<0) {
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return EXIT_FAILURE;
    }
    usleep(100);
    out = m_oDrivePort->readFromPort();
    if (out == INVALID_PROPERTY ||out ==  INVALID_COMMAND_FORMAT ||out ==  UNKNOWN_COMMAND) {
        std::cout<<out<<std::endl;
        std::cout<<ERROR_COMMAND_READ<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout << out << std::endl;
    float pos =std::stof(out);
    return pos;
}

float oDrive::getPosCircular(int axis)
{
    std::string out;
    std::string command = "r axis"+std::to_string(axis)+".encoder.pos_circular";
    if (m_oDrivePort->writeToPort(command)<0) {
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return EXIT_FAILURE;
    }
    usleep(100);
    out = m_oDrivePort->readFromPort();
    if (out == INVALID_PROPERTY ||out ==  INVALID_COMMAND_FORMAT || out == UNKNOWN_COMMAND) {
        std::cout<<ERROR_COMMAND_READ<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout << out << std::endl;
    float pos =std::stof(out);
    return pos;
}
int oDrive::getLockinVelocity(int axis){
    std::string command = "r axis"+std::to_string(axis)+".config.general_lockin.vel";
    std::string out;
    if (m_oDrivePort->writeToPort(command)<0) {
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return EXIT_FAILURE;
    }
    usleep(100);
    out = m_oDrivePort->readFromPort();
    if (out == INVALID_PROPERTY || out ==  INVALID_COMMAND_FORMAT || out ==  UNKNOWN_COMMAND) {
        std::cout<<ERROR_COMMAND_READ<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout << out << std::endl;
    return EXIT_SUCCESS;
}

float oDrive::getPosInTurns(int axis){
    std::string command = "f "+std::to_string(axis);
    std::string out;
    std::string delimiter = " ";
    float pos;
    if(m_oDrivePort->writeToPort(command)<0){
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return 0;
    }
    usleep(100);
    out = m_oDrivePort->readFromPort();
    if (out == INVALID_PROPERTY || out == INVALID_COMMAND_FORMAT || out == UNKNOWN_COMMAND) {
        std::cout<<ERROR_COMMAND_READ<<std::endl;
        return EXIT_FAILURE;
    }
    pos =stof(out.substr(0,out.find(delimiter)));
    return pos;
}
int oDrive::setPosInTurns(int axis,float pos){
    std::string command = "q "+std::to_string(axis)+" "+std::to_string(pos);
    std::string out;
    std::string delimiter = " ";
    if(m_oDrivePort->writeToPort(command)<0){
        std::cout<<ERROR_COMMAND_WRITE<<std::endl;
        return 0;
    }
    usleep(100);
    return EXIT_SUCCESS;
}
oDrive::~oDrive() {
    delete m_oDrivePort;
    // TODO Auto-generated destructor stub
}

