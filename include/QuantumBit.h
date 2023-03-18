#ifndef QUANTUMBIT_H
#define QUANTUMBIT_H

#include <iostream>

#include "RegularAmplitude.h"

class QuantumBit {
public:
    // Constructor
    QuantumBit();

    // Public methods
    void setAmplitude(RegularAmplitude amplitude);

    void print_qubit();

    friend std::ostream& operator<<(std::ostream& s, const QuantumBit& p);

private: 
    RegularAmplitude amplitude;
};

QuantumBit::QuantumBit(){
}


std::ostream& operator<<(std::ostream& s, const QuantumBit& p) {
    return s << p.amplitude;
}

void QuantumBit::setAmplitude(RegularAmplitude amplitude){
    this->amplitude = amplitude;
}

void QuantumBit::print_qubit(){
    std::cout << this->amplitude;
}

#endif
