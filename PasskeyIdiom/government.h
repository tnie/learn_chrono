#pragma once
#include <string>
#include <iostream>
#include "citizen.h"

using std::cout;
using std::endl;

class Government {
private:
    void printCitizenInfo(const Citizen &citizen) const;
};

void Government::printCitizenInfo(const Citizen &citizen) const {
    cout << "Citizen Name: " << citizen.getName() << endl;
    cout << "Citizen SSN: " << citizen.getSocialSecurityNumber(Passkey<Government>()) << endl; // THIS COMPILES
}