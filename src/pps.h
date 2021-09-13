/*
 * pps.h
 *
 *  Created on: 17. 8. 2021
 *      Author: martinek
 */

#ifndef PPS_H_
#define PPS_H_

#include <string>
#include <condition_variable>
#include <mutex>

using namespace std;

class pps {
private:
	bool m_synced=false;
	int m_fd;
	void syncPPS();
	int openPPS();;
	string m_ppsFileName;
protected:


public:
	pps();
	pps(string ppsName);
	struct ppsSignal{
		string time = "0";
		//double time=0.000000000;
		int cnt=0;
	};
	ppsSignal m_actual;
	//ppsSignal getPPS();
	int getPPS();

	virtual ~pps();
};

#endif /* PPS_H_ */
