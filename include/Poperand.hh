#ifndef POPERAND_HH
#define POPERAND_HH

#include "Operand.hh"

class Poperand : public Operand {
public:
    Poperand(const std::string& raw);

    // Virtual methods
    void identifyChild() const override;
    void printValue() const;

};

#endif
