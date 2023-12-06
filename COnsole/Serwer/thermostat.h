#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <iostream>

class Thermostat {
public:
    Thermostat();

    int getValue();
    void setValue(int value);


    int thermostatValue;
};

#endif
