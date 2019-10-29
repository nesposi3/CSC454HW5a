//
// Created by nick on 10/29/19.
//

#include "VendingMachine.h"
#define INFINITY 2147483647
#define EPSILON .0001

#include "TimePair.h"
std::string VendingMachine::lambda() {
    std::string out = " {OUT: ";
    int val = this->value;
    while (val >= 100) {
        //vend coffee
        out.append(" COFFEE ");
        val -= 100;
    }
    int* changeBack = this->getChange(val, this->quarter, this->dime, this->nickel);
    int q = changeBack[0];
    int d = changeBack[1];
    int n = changeBack[2];
    if (q != 0 || d != 0 || n != 0) {
        if (q > 0) {
            out.append(std::to_string(q) + " QUARTERS ");
        }
        if (d > 0) {
            out.append(std::to_string(d) + " DIMES ");
        }
        if (n > 0) {
            out.append(std::to_string(n) + " NICKELS ");
        }
    }
    delete changeBack;
    out.append("}");
    return out;
}

void VendingMachine::deltaInt() {
    int* change = this->getChange(this->value, this->quarter, this->dime, this->nickel);
    this->quarter -= change[0];
    this->dime -= change[1];
    this->nickel -= change[2];
    this->value = 0;
    delete change;
}

void VendingMachine::deltaExt(char inp) {
    if (inp == 'q') {
        this->quarter++;
        this->value += 25;
    } else if (inp == 'd') {
        this->dime++;
        this->value += 10;
    } else if (inp == 'n') {
        this->nickel++;
        this->value += 5;
    }

}

void VendingMachine::deltaConf(char inp) {
    int* change = this->getChange(this->value, this->quarter, this->dime, this->nickel);
    this->value = 0;

    if(inp == 'q'){
        this->quarter++;
        this->value = 25;
    }else if(inp == 'd'){
        this->dime++;
        this->value = 10;
    }else if(inp=='n'){
        this->nickel++;
        this->value = 5;
    }
    this->quarter -= change[0];
    this->dime -= change[1];
    this->nickel -= change[2];
    delete change;
}

void VendingMachine::simulate(std::vector<std::string> inp,bool debug) {
        TimePair previousTime = TimePair(0.0);
        TimePair internalTime = previousTime.advanceBy(2.0);
        for (int i = 0; i < inp.size(); i++) {
            std::string currString = inp.at(i);
            double time = std::stod(currString.substr(0,currString.find(',')));
            char inputChar =currString.substr(currString.find(',')+1)[0];
            double timeElapsed;
            TimePair timePair = TimePair(time);
            timeElapsed = timePair.getReal() - previousTime.getReal();
            internalTime = previousTime.advanceBy(2.0);
            previousTime = timePair;
            // Run lambda/delta
            if (TimePair::compareReals(timeElapsed, timeAdvance(),EPSILON) >= 0) {
                // There should be an internal/confluent delta before this input
                if (TimePair::compareReals(timeElapsed, timeAdvance(),EPSILON) == 0) {
                    // Input on same time as timeAdvance, confluent case
                    std::string debuginfo;
                    if(debug){
                        debuginfo = "{INP:" + std::to_string(inputChar) +"}";
                    }
                    std::cout<< internalTime.toString() + debuginfo+ lambda() << std::endl;
                    deltaConf(inputChar);
                } else {
                    // Input in-between, internal case
                    std::cout<< internalTime.toString() +  lambda() << " Delta Int" <<std::endl;
                    deltaInt();
                    // This must also be run for the input after the internal case
                    if(debug){
                        std::cout<<timePair.toString() + " "<< "{INP:" <<(char) inputChar << "} Delta External"<< std::endl;
                    }
                    deltaExt(inputChar);
                }
            } else {
                // No waiting, external case
                if(debug){
                    std::cout<<timePair.toString() + " "<< "{INP:" << (char) inputChar << "} Delta External"<< std::endl;
                }
                deltaExt(inputChar);
            }
        }
        if (TimePair::compareReals(2.0, timeAdvance(),EPSILON) == 0) {
            internalTime = previousTime.advanceBy(2.0);
            // Another lambda and internal delta must be executed after input trajectory
            std::cout<< internalTime.toString() + lambda() << " Delta Int" <<std::endl;
            deltaInt();
        }
    }

int* VendingMachine::getChange(int val, int quarter, int dime, int nickel) {
    int *out = new int;
    int q = 0;
    int n = 0;
    int d = 0;
    while (q * 25 <= val - 25) {
        q++;
    }
    val -= (q * 25);
    while (d * 10 <= val - 10) {
        d++;
    }
    val -= (d * 10);
    while (n * 5 <= val - 5) {
        n++;
    }
    val -= (n * 5);
    if (val != 0 || (q > quarter) || (d > dime) || (n > nickel)) {
        //TODO Decide on logic for exception case
    }
    out[0] = q;
    out[1] = d;
    out[2] = n;
    return out;
}

double VendingMachine::timeAdvance() {
    if(this->value>0){
        return 2;
    } else{
        return INFINITY;
    }
}
