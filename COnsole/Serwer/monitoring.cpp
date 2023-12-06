#include "monitoring.h"
#include <iostream>
#include <thread>
#include <unistd.h>

Monitoring::Monitoring() : timeToCall(10) {
    std::thread t(&Monitoring::monitoringCheck, this);
    t.detach();
}



void Monitoring::monitoringCheck() {  // Removed the parameter here
    while (true) {
        checkAndCall();
        sleep(1);
    }
}

void Monitoring::callToDoorbell() { // Corrected function name to callToDoorbell
    std::cout << "DORBELL!!!" << std::endl
              << "DORBELL!!!" << std::endl
              << "DORBELL!!!" << std::endl
              << "DORBELL!!!" << std::endl
              << "DORBELL!!!" << std::endl
              << "DORBELL!!!" << std::endl;
    sleep(5);
}
void Monitoring::checkAndCall() {
    if (timeToCall <= 0) {
        callToDoorbell(); // Corrected function name to callToDoorbell
        timeToCall = 100;
    } else {
        timeToCall--;
    }
}