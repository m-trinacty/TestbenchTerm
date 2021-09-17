/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef PPS_H_
#define PPS_H_

#include <string>
#include <condition_variable>
#include <mutex>


class pps {
private:
	bool m_synced=false;
	int m_fd;
	void syncPPS();
	int openPPS();;
    std::string m_ppsFileName;
protected:


public:
	pps();
    pps(std::string ppsName);
	struct ppsSignal{
        std::string time = "0";
		//double time=0.000000000;
		int cnt=0;
	};
	ppsSignal m_actual;
	//ppsSignal getPPS();
	int getPPS();

	virtual ~pps();
};

#endif /* PPS_H_ */
