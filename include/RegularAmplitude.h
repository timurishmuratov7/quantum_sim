#ifndef REGULARAMPLITUDE_H
#define REGULARAMPLITUDE_H

class RegularAmplitude {
public:
    // Constructor
    RegularAmplitude();
    RegularAmplitude(int x1, int x2);

// [x1, x2] - state of one qbit
private:
    int x1;
    int x2;
};


RegularAmplitude::RegularAmplitude(){
    this->x1 = 0;
    this->x2 = 0;
}


RegularAmplitude::RegularAmplitude(int x1, int x2){
    this->x1 = x1;
    this->x2 = x2;
}

#endif
