/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include <sstream>
#include <iomanip>
#include <thread>
#include <fstream>

#include "oDrive.h"
#include "pps.h"
#include "logger.h"
#include "helper.h"
#define STOP 0

int main(int argc,char * argv[] ) {
#if STOP

    const std::string portName = "/dev/oDrive";
    std::unique_ptr<oDrive> odrive(new oDrive(portName));
    odrive->setVelocity(0,0);

#else
    if(argc!=4){
        std::cout<<"Not enough arguments"<<std::endl;
        return EXIT_FAILURE;
    }

    const std::string portName = "/dev/oDrive";
    std::unique_ptr<oDrive> odrive(new oDrive(portName));
    odrive->clearErrors(0);
    odrive->getMinEndstop(0)?std::cout<<"True"<<std::endl:std::cout<<"False"<<std::endl;
    odrive->setHoming(0);

    odrive->getMinEndstop(0)?std::cout<<"True"<<std::endl:std::cout<<"False"<<std::endl;
    odrive->clearErrors(0);
    odrive->setMinEndstop(0,false);

    odrive->getMinEndstop(0)?std::cout<<"True"<<std::endl:std::cout<<"False"<<std::endl;
    odrive->clearErrors(0);
    std::cout<<"Closed loop"<<std::endl;
    std::cout<<argv[1]<<std::endl;
    odrive->setAxisState(0,odrive->AXIS_STATE_CLOSED_LOOP_CONTROL);

    float posCircular=odrive->getPosCircular(0);
    float posEstimate=odrive->getPosEstimate(0);
    float posEstimateCounts = odrive->getPosEstimateCounts(0);
    float posInTurns = odrive->getPosInTurns(0);
    float IqMeasurd = odrive->getIqMeasured(0);

    float velF=0.0;

    auto now=std::chrono::system_clock::now();
    auto nowTime =  std::chrono::system_clock::to_time_t(now);
    auto start = std::chrono::steady_clock::now();

    std::stringstream ss;
    std::stringstream fileName;


    fileName << std::put_time(std::localtime(&nowTime),"%Y-%m-%d_%X");
    std::ofstream spinLog("logs/"+std::string(argv[3])+"_"+fileName.str()+".log");

    ss<<std::put_time(std::localtime(&nowTime),"%Y-%m-%d %X");
    spinLog<<Logger::header();

    spinLog<<std::endl<<Logger::getTime()<<std::endl;
    spinLog<<"HOMING POSITION"<<std::endl<<Logger::record(posCircular,posEstimate,posEstimateCounts,posInTurns,IqMeasurd)<<std::endl<<"HOMING POSITION"<<std::endl;


    if(Helper::isNumber(argv[1])){
        std::string velS(argv[1]);
        velF= std::stof(velS);
        if(velF<=70){
            std::cout<<"userVel="<<velF<<std::endl;
            odrive->setVelocity(0,velF);
        }
        else{
            return EXIT_FAILURE;
        }
    }
    else{
        return EXIT_FAILURE;
    }
    spinLog<<"Velocity = "<<std::to_string(velF)<<std::endl;


    auto endTime =std::chrono::seconds(1);

    if(Helper::isNumber(argv[2])){
        std::string timeS(argv[2]);
        int timeInt= std::stoi(timeS);
        endTime = std::chrono::seconds(timeInt);
    }
    else{
        return EXIT_FAILURE;
    }



    auto timer = std::chrono::milliseconds(10);

    while(1)
    {
        if(std::chrono::steady_clock::now() - (start+timer) > std::chrono::milliseconds(1))
        {
            posCircular=odrive->getPosCircular(0);
            posEstimate=odrive->getPosEstimate(0);
            posEstimateCounts = odrive->getPosEstimateCounts(0);
            posInTurns = odrive->getPosInTurns(0);
            IqMeasurd= odrive->getIqMeasured(0);

            spinLog<<Logger::record(posCircular,posEstimate,posEstimateCounts,posInTurns,IqMeasurd)<<std::endl;
        }
        if(std::chrono::steady_clock::now()- start> endTime)
        {
            std::cout<<"Velocity" <<odrive->getVelocity(0)<<std::endl;
            //opacny smer minus, doimplementovat
            float stopVel=odrive->getVelocity(0);
            if(stopVel<0.05||stopVel>-0.05)
                break;
        }
    }
#endif
    odrive->setAxisState(0,odrive->AXIS_STATE_IDLE);


    return 0;
};
