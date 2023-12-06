#include "door.h"
using namespace std;
Door::Door() : doorStatus(false) {}

bool Door::checkStatus(){
    return doorStatus;
}

void Door::setStatus(bool newStatus) {
    doorStatus = newStatus;
    
}
