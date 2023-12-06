#ifndef GATE_AND_GARAGE_H
#define GATE_AND_GARAGE_H

#include <iostream>

class GateAndGarage {
public:
    GateAndGarage();

    bool checkStatus();
    void setStatus(bool newStatus);

private:
    bool gateAndGarageStatus;
};

#endif
