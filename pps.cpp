/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "pps.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()



pps::pps() {
	// TODO Auto-generated constructor stub

}
pps::pps(std::string ppsName){
	m_ppsFileName = ppsName;
	syncPPS();
}

void pps::syncPPS(){

	while(!m_synced){
		if(getPPS()!=EXIT_SUCCESS){
            std::cout<<"Could not get PPS info"<< std::endl;
		}
		if (m_actual.cnt>0) {
			m_synced=true;
            std::cout<<"PPS is synced"<<std::endl;
		}
	}

}
int pps::openPPS(){
	const char * ppsFile=m_ppsFileName.c_str();

	if((m_fd = open(ppsFile,O_RDONLY)) < 0){
        std::cout << "Error "<< errno << " from open: " << strerror(errno) << std::endl;
        return 0;
	}

	return EXIT_SUCCESS;
}
int pps::getPPS(){
	if(openPPS()!=EXIT_SUCCESS){
        std::cout<<"Could not open PPS file"<<std::endl;
        return 0;
	}
	m_actual.cnt=-1;
	m_actual.time="-1.1";
	char readBuf [256];
	memset(readBuf,'\n',sizeof(readBuf));
	int numBytes=read(m_fd,&readBuf,sizeof(readBuf));
	if (numBytes < 0) {
         std::cout << "ERROR "<< errno << " reading: " << strerror(errno) << std::endl;
        return 0;
	}
	if(numBytes== 0){
        std::cout << "PPS signal was not read"<<std::endl;
        return 0;
	}
	if(numBytes>0){
        std::string delimiter = "#";
        std::string output = "";
		for (int i = 0; i < 256; ++i) {
			if(readBuf[i]=='\n'){
				break;
			}
			output = output + readBuf[i];
		}
        std::string time=output.substr(0,output.find(delimiter));
        std::string cnt = output.substr(output.find(delimiter)+1,output.length()-1);
		m_actual.time = time;
		m_actual.cnt = stoi(cnt);
	}
	if(close(m_fd)!= EXIT_SUCCESS){
        std::cout << "ERROR "<< errno << " closing: " << strerror(errno) << std::endl;
        return 0;
	}
	return EXIT_SUCCESS;
}

pps::~pps() {
	// TODO Auto-generated destructor stub
}

