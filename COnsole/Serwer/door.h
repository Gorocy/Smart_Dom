#ifndef DOOR_H
#define DOOR_H

#include <iostream>

class Door {
public:
    Door();

    bool checkStatus();
    void setStatus(bool newStatus);

private:
    bool doorStatus;
};

#endif

