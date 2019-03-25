#pragma once
#include <string>
#include "passkey.h"

using std::string;

class Government;
class Citizen {
public:
    string getName() const;
    string getSocialSecurityNumber(Passkey<Government>) const;

private:
    string getFavouriteFood() const;

    string _name;
    string _favouriteFood;
    string _socialSecurityNumber;
};

string Citizen::getName() const {
    return _name;
}

string Citizen::getFavouriteFood() const {
    return _favouriteFood;
}

string Citizen::getSocialSecurityNumber(Passkey<Government>) const {
    return _socialSecurityNumber;
}
