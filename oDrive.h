/*
 * Copyright (C) Aero4TE, s.r.o. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef ODRIVE_H_
#define ODRIVE_H_

#include <string>
#include "port.h"


class oDrive {
private:
    port * m_oDrivePort;

public:

    oDrive();
    enum AxisState{
        AXIS_STATE_UNDEFINED,
        AXIS_STATE_IDLE,
        AXIS_STATE_STARTUP_SEQUENCE,
        AXIS_STATE_FULL_CALIBRATION_SEQUENCE,
        AXIS_STATE_MOTOR_CALIBRATION,
        AXIS_STATE_DUMMY_DO_NOT_USE,
        AXIS_STATE_ENCODER_INDEX_SEARCH,
        AXIS_STATE_ENCODER_OFFSET_CALIBRATION,
        AXIS_STATE_CLOSED_LOOP_CONTROL,
        AXIS_STATE_LOCKIN_SPIN,
        AXIS_STATE_ENCODER_DIR_FIND,
        AXIS_STATE_HOMING,
        AXIS_STATE_ENCODER_HALL_POLARITY_CALIBRATION,
        AXIS_STATE_ENCODER_HALL_PHASE_CALIBRATION
    };
    oDrive(std::string portName);
    int commandConsole();
    virtual ~oDrive();
    int setState(int axis, int state);
    int setVelocity(int axis, float vel);
    int setLockinVelocity(int axis, float vel);
    float getPosEstimate(int axis);
    float getPosEstimateCounts(int axis);
    float getPosCircular(int axis);
    int getLockinVelocity(int axis);
    float getPosInTurns(int axis);
    int setPosInTurns(int axis, float pos);

};


#endif /* ODRIVE_H_ */
