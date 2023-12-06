#include "pet_feeder.h"
#include <iostream>

PetFeeder::PetFeeder() : petFeederStatus(false), hour(18) {}

void PetFeeder::dispenseFood() {
    std::cout << "FEEDING" << std::endl;
    // Tutaj możesz umieścić kod sterujący karmieniem zwierzęcia
}

void PetFeeder::setDispenseFood(int dispenseFoodTime) {
    hour = dispenseFoodTime;
}

int PetFeeder::getHour() const {
    return hour;
}
