#include <iostream>
#include <fstream>
#include <vector>
#include "VendingMachine.h"

int main(int argc, char** argv) {
    bool debug = false;
    std::ifstream infile;
    std::string fileName = "./traj.txt";
    if(argc>1){
        for (int i = 1; i <argc ; ++i) {
            std::string argi = std::string(argv[i]);
            if(argi == "-d" || argi == "--debug" ){
                debug= true;
            }else{
                fileName = argi;
            }
        }
    }
    infile.open(fileName);
    std::string line;
    std::vector<std::string> inputVector = std::vector<std::string>();
    if(infile.is_open()){
        while (std::getline(infile,line)) {
            inputVector.push_back(line);
        }
    }

    std::cout << inputVector.size() << std::endl;
    infile.close();
    VendingMachine vendingMachine = VendingMachine();
    vendingMachine.simulate(inputVector,debug);
}