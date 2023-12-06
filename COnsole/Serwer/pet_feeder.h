#ifndef PET_FEEDER_H
#define PET_FEEDER_H

class PetFeeder {
public:
    bool petFeederStatus;
    int hour;

    PetFeeder();

    void dispenseFood();

    void setDispenseFood(int dispenseFoodTime);

    int getHour() const;
};

#endif //PET_FEEDER_H
