#ifndef FOPERAND_HH
#define FOPERAND_HH

#include "Operand.hh"

class Foperand : public Operand {
public:
    Foperand(const std::string& raw);

    void identifyChild() const override;
    void printValue() const;
    // void printValue() const override;
};

#endif
