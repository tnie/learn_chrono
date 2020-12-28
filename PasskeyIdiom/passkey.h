#pragma once

template<typename T>
class Passkey {
private:  // CAN'T BE public
//public:
    friend T;
    Passkey() {};   // CAN'T `= default;`
    Passkey(const Passkey&) {};
    Passkey& operator=(const Passkey&) = delete;
};
