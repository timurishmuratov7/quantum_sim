#include <iostream>
#include "QuantumBit.h"
#include "RegularAmplitude.h"

int main()
{
    QuantumBit qbit;

    RegularAmplitude regamp(0, 1);

    qbit.setAmplitude(regamp);
    std::cout << "Welcome to quantum" << std::endl;
}