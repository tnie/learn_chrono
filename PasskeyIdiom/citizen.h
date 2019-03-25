#pragma once
#include <string>

using std::string;

class Citizen {
    friend class Government;

    // The side effect, however, is that the government now knows the citizen's favourite food. \
That's obviously an unacceptable privacy violation!
public:
    string getName() const;

private:
    string getFavouriteFood() const;
    string getSocialSecurityNumber() const;

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

string Citizen::getSocialSecurityNumber() const {
    return _socialSecurityNumber;
}
