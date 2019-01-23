#ifndef rotary_h
#define rotary_h

#include <Arduino.h>

class Rotary {
    public:
        Rotary(int p1, int p2, int p3, int p4);
        int getPosition();
        void init();
    private:
        int p1, p2, p3, p4;
}; 


Rotary::Rotary(int _p1, int _p2, int _p3, int _p4){
    this->p1 = _p1;
    this->p2 = _p2;
    this->p3 = _p3;
    this->p4 = _p4;
};

void Rotary::init(){
    pinMode(p1, INPUT);
    pinMode(p2, INPUT);
    pinMode(p3, INPUT);
    pinMode(p4, INPUT);
}

int Rotary::getPosition(){
    uint8_t out = 0;
    bitWrite(out, 0, digitalRead(p1));
    bitWrite(out, 1, digitalRead(p2));
    bitWrite(out, 2, digitalRead(p3));
    bitWrite(out, 3, digitalRead(p4));
    return out;
}

#endif