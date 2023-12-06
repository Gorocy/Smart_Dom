#pragma once
#ifndef ROLLER_SHUTTER_H
#define ROLLER_SHUTTER_H

#include <iostream>

class RollerShutter {
public:
    RollerShutter();

    bool checkStatus() ;
    void setStatus(bool newStatus);

private:
    bool shutterStatus;
};

#endif

