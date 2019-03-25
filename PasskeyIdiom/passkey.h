#pragma once

template<typename T>
class Passkey {
private:
    friend T;
    Passkey() = default;
    Passkey(const Passkey&) = default;
    Passkey& operator=(const Passkey&) = delete;
};
