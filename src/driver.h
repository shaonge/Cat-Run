//
// Created by 14667 on 2018/2/4.
//

#ifndef PROGRAMMABLECALCULATOR_FILE_DRIVER_H
#define PROGRAMMABLECALCULATOR_FILE_DRIVER_H

#include "context.h"

#include <iosfwd>

namespace ssg {

class Scanner;
class Parser;

class Driver {
  public:
    void parse(const char *filename);

    void parse(std::istream &iss);

    ~Driver();

  private:
    void parse_helper(std::istream &iss);

  private:
    Scanner *scanner = nullptr;
    Parser *parser = nullptr;
    Context *context = nullptr;
};
} // namespace ssg

#endif // PROGRAMMABLECALCULATOR_FILE_DRIVER_H
