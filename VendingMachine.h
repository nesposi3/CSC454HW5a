//
// Created by nick on 10/29/19.
//

#ifndef CSC454HW5A_VENDINGMACHINE_H
#define CSC454HW5A_VENDINGMACHINE_H


#include <iostream>
#include <vector>

class VendingMachine {
private:
    int  quarter, dime, nickel, value;
    int * getChange(int val, int quarter, int dime, int nickel);
    double timeAdvance();
    std::string lambda();
    void deltaInt();
    void deltaExt(char inp);
    void deltaConf(char inp);
public:
    VendingMachine() {
        this->quarter = 0;
        this->dime = 0;
        this->nickel = 0;
        this->value = 0;
    }
    VendingMachine(int quarter, int dime, int nickel, int value) {
        this->quarter = quarter;
        this->dime = dime;
        this->nickel = nickel;
        this->value = value;
    }
    void simulate(std::vector<std::string> inp, bool debug);
};


#endif //CSC454HW5A_VENDINGMACHINE_H
