#pragma once
#include "citizen.h"
#include <iostream>
using std::cout;
using std::endl;
class Spy {
private:
    void printCitizenInfo(const Citizen &citizen) const;
};

void Spy::printCitizenInfo(const Citizen &citizen) const {
    cout << "Citizen Name: " << citizen.getName() << endl;
    cout << "Citizen SSN: " << citizen.getSocialSecurityNumber() << endl; // COMPILE ERROR
}
