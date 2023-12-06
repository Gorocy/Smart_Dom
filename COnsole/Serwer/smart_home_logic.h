#ifndef SMART_HOME_LOGIC_H
#define SMART_HOME_LOGIC_H

#include "monitoring.h"
#include "door.h"
#include "gate_and_garage.h"
#include "pet_feeder.h"
#include "roller_shutter.h"
#include "thermostat.h"
#include <string>


class SmartHomeLogic {
public:
    Monitoring monitoring;

    Door door[4];
    GateAndGarage gateAndGarage;
    PetFeeder petFeeder;
    RollerShutter rollerShutter[4];
    Thermostat thermostat;



    SmartHomeLogic();
    //door
    void controlDoor(int a, bool open);
    bool checkDoor(int a);
    //gate
    void controlGateAndGarage(bool open);
    bool checkGateAndGarage();
    //pet
    int checkPetFeeder();
    void feedingPet();
    //rollerShutter
    bool checkRollerShutter(int a);
    void controlRollerShutter(int a, bool newStatus);
    //temperature
    void setThermostat(int value);
    int checkThermostat();

    void setTimeFeeding(int time);

    void getSystemStatus();
};

#endif
