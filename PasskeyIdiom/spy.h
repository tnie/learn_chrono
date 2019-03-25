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
    //cout << "Citizen SSN: " << citizen.getSocialSecurityNumber(Passkey<Spy>()) << endl; // COMPILE ERROR
    // ��� PassKey �Ĺ����� public���˴����ܹ�����ͨ��
    //cout << "Citizen SSN: " << citizen.getSocialSecurityNumber(Passkey<Government>()) << endl; // COMPILE ERROR
    cout << "Citizen SSN: " << citizen.getSocialSecurityNumber({}) << endl; // THIS COMPILES if `Passkey() = default`
}
