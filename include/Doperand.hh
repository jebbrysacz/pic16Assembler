#ifndef DOPERAND_HH
#define DOPERAND_HH

#include "Operand.hh"

class Doperand : public Operand {
public:
    Doperand(const std::string& raw);

    void identifyChild() const override;
    void printValue() const;
    // void printValue() const override;
};

#endif
