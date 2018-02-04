//
// Created by 14667 on 2018/2/3.
//

#include "driver.h"

#include <iostream>

int main() {
    gss::Driver driver;
    std::cout << "> " << std::flush;
    driver.parse(std::cin);
}
