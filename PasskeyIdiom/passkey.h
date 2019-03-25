#pragma once

template<typename T>
class Passkey {
private:  // CAN'T BE public
//public:
    friend T;
    Passkey() {};
    Passkey(const Passkey&) {};
    Passkey& operator=(const Passkey&) = delete;
};
