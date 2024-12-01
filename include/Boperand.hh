#ifndef BOPERAND_HH
#define BOPERAND_HH

#include "Operand.hh"

class Boperand : public Operand {
public:
    Boperand(const std::string& raw);

    // // Equality operators
    // bool operator==(const Boperand &other) const {
    //     return raw == other.raw && size == other.size && binary == other.binary;
    // }

    // bool operator!=(const Boperand &other) const {
    //     return !(*this == other);
    // }

    // Virtual methods
    void identifyChild() const override;
    void printValue() const;
    // void printValue() const override;
};

#endif
