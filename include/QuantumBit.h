#ifndef QUANTUMBIT_H
#define QUANTUMBIT_H

#include "RegularAmplitude.h"

class QuantumBit {
public:
    // Constructor
    QuantumBit();

    // Public methods
    void setAmplitude(RegularAmplitude amplitude);

private: 
    RegularAmplitude amplitude;
};

QuantumBit::QuantumBit(){
}

void QuantumBit::setAmplitude(RegularAmplitude amplitude){
    this->amplitude = amplitude;
}

#endif
