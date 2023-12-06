#include "gate_and_garage.h"
using namespace std;
GateAndGarage::GateAndGarage() : gateAndGarageStatus(false) {}

bool GateAndGarage::checkStatus(){
    return gateAndGarageStatus;
}

void GateAndGarage::setStatus(bool newStatus) {
    gateAndGarageStatus = newStatus;

}
