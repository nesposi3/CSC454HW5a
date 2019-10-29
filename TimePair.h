//
// Created by nick on 10/29/19.
//

#ifndef CSC454HW5A_TIMEPAIR_H
#define CSC454HW5A_TIMEPAIR_H

#include <iostream>
class TimePair {
private:
    double real;
    int discrete;
public:
    static int compareReals(double a, double b,double epsilon);
    double getReal();
    int getDiscrete();
    TimePair(double real);
    TimePair(double real, int discrete);
    std::string toString();
    TimePair advanceBy(TimePair disp);
    TimePair advanceBy(double real);
};


#endif //CSC454HW5A_TIMEPAIR_H
