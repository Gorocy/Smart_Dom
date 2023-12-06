#include "thermostat.h"
using namespace std;
Thermostat::Thermostat() : thermostatValue(20) {}

int Thermostat::getValue()  {
    return thermostatValue;
}

void Thermostat::setValue(int value) {
    if (value < 0) { thermostatValue = 0;  }
    else if (value > 30) { thermostatValue = 30; }
    else{ thermostatValue = value; }
    
}
