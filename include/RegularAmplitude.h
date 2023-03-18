#ifndef REGULARAMPLITUDE_H
#define REGULARAMPLITUDE_H

class RegularAmplitude {
public:

    int x1;
    int x2;

    // Constructor
    RegularAmplitude(): x1(0), x2(0) {}
    RegularAmplitude(int x1, int x2): x1(x1), x2(x2) {}

    // public methods

};

std::ostream& operator<<(std::ostream &s, const RegularAmplitude &amplitude) {
    return s << "(" << amplitude.x1 << ", " << amplitude.x2 << ")";
}

#endif
