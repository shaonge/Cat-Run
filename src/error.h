//
// Created by 14667 on 2018/2/4.
//

#ifndef PROGRAMMABLECALCULATOR_FILE_ERROR_H
#define PROGRAMMABLECALCULATOR_FILE_ERROR_H

#include <cstdlib>
#include <iostream>

static void runtime_error() { exit(EXIT_FAILURE); }

template <typename T, typename... Args> static void runtime_error(T t, Args... args) {
    std::cout << t;
    runtime_error(args...);
}

#endif // PROGRAMMABLECALCULATOR_FILE_ERROR_H
