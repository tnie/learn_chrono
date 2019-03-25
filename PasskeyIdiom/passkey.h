#pragma once

template<typename T>
class Passkey {
private:  // CAN'T BE public
//public:
    friend T;
    Passkey() = default;
    //Passkey() {};
    Passkey(const Passkey&) = default;
    Passkey& operator=(const Passkey&) = delete;
};
