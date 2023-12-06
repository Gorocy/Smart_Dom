#include "roller_shutter.h"
using namespace std;
RollerShutter::RollerShutter() : shutterStatus(false) {}

bool RollerShutter::checkStatus() {
    return shutterStatus;
}

void RollerShutter::setStatus(bool newStatus) {
    shutterStatus = newStatus;
    
}
