//
// Created by nick on 10/29/19.
//

#include "TimePair.h"
#include <math.h>
int TimePair::getDiscrete() {
    return this->discrete;
}

double TimePair::getReal() {
    return this->real;
}

int TimePair::compareReals(double a, double b,double epsilon) {
    if(fabs(a-b) < epsilon){
        //Equal with tolerance
        return 0;
    }else if( (a-b) > 0){
        //A greater than B
        return 1;
    }else{
        return -1;
    }

}

TimePair::TimePair(double real) {
    this->real = real;
    this->discrete = 0;
}

TimePair::TimePair(double real, int discrete) {
    this->real = real;
    this->discrete = discrete;
}

std::string TimePair::toString() {
    return "{ "+ std::to_string(real) + " " + std::to_string(discrete) + " }";
}

TimePair TimePair::advanceBy(double real) {
    double advanced = real + this->real;
    return TimePair(advanced);
}

TimePair TimePair::advanceBy(TimePair disp) {
    double advanced = disp.real + this->real;
    int advancedDisc = disp.discrete + this->discrete;
    return TimePair(advanced,advancedDisc);
}
