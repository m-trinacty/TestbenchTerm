/*
 * pps.cpp
 *
 *  Created on: 17. 8. 2021
 *      Author: martinek
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

using namespace std;

pps::pps() {
	// TODO Auto-generated constructor stub

}
pps::pps(string ppsName){
	m_ppsFileName = ppsName;
	syncPPS();
}

void pps::syncPPS(){

	while(!m_synced){
		if(getPPS()!=EXIT_SUCCESS){
			cout<<"Could not get PPS info"<< endl;
		}
		if (m_actual.cnt>0) {
			m_synced=true;
			cout<<"PPS is synced"<<endl;
		}
	}

}
int pps::openPPS(){
	const char * ppsFile=m_ppsFileName.c_str();

	if((m_fd = open(ppsFile,O_RDONLY)) < 0){
		cout << "Error "<< errno << " from open: " << strerror(errno) << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
int pps::getPPS(){
	if(openPPS()!=EXIT_SUCCESS){
		cout<<"Could not open PPS file"<<endl;
		return EXIT_FAILURE;
	}
	m_actual.cnt=-1;
	m_actual.time="-1.1";
	char readBuf [256];
	memset(readBuf,'\n',sizeof(readBuf));
	int numBytes=read(m_fd,&readBuf,sizeof(readBuf));
	if (numBytes < 0) {
		cout << "ERROR "<< errno << " reading: " << strerror(errno) << endl;
		return EXIT_FAILURE;
	}
	if(numBytes== 0){
		cout << "PPS signal was not read"<<endl;
		return EXIT_FAILURE;
	}
	if(numBytes>0){
		string delimiter = "#";
		string output = "";
		for (int i = 0; i < 256; ++i) {
			if(readBuf[i]=='\n'){
				break;
			}
			output = output + readBuf[i];
		}
		string time=output.substr(0,output.find(delimiter));
		string cnt = output.substr(output.find(delimiter)+1,output.length()-1);
		m_actual.time = time;
		m_actual.cnt = stoi(cnt);
	}
	if(close(m_fd)!= EXIT_SUCCESS){
		cout << "ERROR "<< errno << " closing: " << strerror(errno) << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

pps::~pps() {
	// TODO Auto-generated destructor stub
}

