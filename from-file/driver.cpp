//
// Created by 14667 on 2018/2/4.
//

#include "driver.h"
#include "scanner.h"

#include <cassert>
#include <fstream>
#include <iostream>

namespace gss {

Driver::~Driver() {
    delete scanner;
    delete parser;
    delete context;
}

void Driver::parse(const char *filename) {
    assert(filename != nullptr);
    std::ifstream in_file(filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }
    parse_helper(in_file);
}

void Driver::parse(std::istream &iss) {
    if (!iss.good() && iss.eof()) {
        return;
    }

    parse_helper(iss);
}

void Driver::parse_helper(std::istream &iss) {
    delete scanner;
    try {
        scanner = new Scanner(&iss);
    } catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate scanner: (" << ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }

    delete context;
    try {
        context = new Context();
    } catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate context: (" << ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }

    delete parser;
    try {
        parser = new Parser(*scanner, *context);
    } catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate parser: (" << ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }

    const int accept = 0;
    if (parser->parse() != accept) {
        std::cerr << "Parse failed!!\n";
    }
}
} // namespace gss
