#include "smart_home_logic.h"
#include <iostream>
#include <string>
using namespace std;



SmartHomeLogic::SmartHomeLogic() {
    cout<<"home logic start"<<endl;

}


void SmartHomeLogic::setThermostat(int value) {
    thermostat.setValue(value);
    cout << "Thermostat set to: " << thermostat.getValue() << " degrees Celsius.\n";
}

int SmartHomeLogic::checkThermostat() {
    return thermostat.getValue();
}


int SmartHomeLogic::checkPetFeeder() {
    
    
    return petFeeder.getHour();
}
void SmartHomeLogic::setTimeFeeding(int time) {
    petFeeder.setDispenseFood(time);
}
void SmartHomeLogic::feedingPet() {
    petFeeder.dispenseFood();
}

bool SmartHomeLogic::checkRollerShutter(int a) {
    return rollerShutter[a].checkStatus();
}

void SmartHomeLogic::controlRollerShutter(int a, bool newStatus) {
    rollerShutter[a].setStatus(newStatus);
    
   
}

void SmartHomeLogic::controlDoor(int a, bool newStatus) {
    door[a].setStatus(newStatus);
   
}
bool SmartHomeLogic::checkDoor(int a) {
    return door[a].checkStatus();
}

void SmartHomeLogic::controlGateAndGarage(bool newStatus) {
    gateAndGarage.setStatus(newStatus);
    if (newStatus) {
        cout << "Gate and garage are open.\n";
    }
    else {
        cout << "Gate and garage are closed.\n";
    }
}
bool SmartHomeLogic::checkGateAndGarage() {
    return gateAndGarage.checkStatus();
}




void SmartHomeLogic::getSystemStatus() {
    cout << "Thermostat: " << thermostat.getValue() << " degrees Celsius\n";
    cout << "Pet Feeder: " << (petFeeder.getHour() > 0 ? "Open" : "Closed") << "\n";
    cout << "Door: " << (door[0].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Door: " << (door[1].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Door: " << (door[2].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Door: " << (door[3].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Roller Shutter: " << (rollerShutter[0].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Roller Shutter: " << (rollerShutter[1].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Roller Shutter: " << (rollerShutter[2].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Roller Shutter: " << (rollerShutter[3].checkStatus() ? "Open" : "Closed") << "\n";
    cout << "Gate and Garage: " << (gateAndGarage.checkStatus() ? "Open" : "Closed") << "\n";

}
