//
// Created by 14667 on 2018/2/3.
//

#include "driver.h"
#include "driver.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        ssg::Driver driver;
        driver.parse(argv[1]);
    } else {
        std::cout << "usage: pc [file]\n"
                  << "\tpc:        a command line calculator\n"
                  << "\tpc file:   interpret and run this file\n";
    }
}
