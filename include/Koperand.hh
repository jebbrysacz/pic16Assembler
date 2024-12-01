#ifndef KOPERAND_HH
#define KOPERAND_HH

#include "Operand.hh"

class Koperand : public Operand {
public:
    Koperand(const std::string& raw);

    void identifyChild() const override;
    void printValue() const;
    // void printValue() const override;
};

#endif
