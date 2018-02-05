//
// Created by 14667 on 2018/2/4.
//

#ifndef PROGRAMMABLECALCULATOR_DRIVER_H
#define PROGRAMMABLECALCULATOR_DRIVER_H

#include "context.h"

#include <iosfwd>

namespace gss {

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
} // namespace gss

#endif // PROGRAMMABLECALCULATOR_DRIVER_H
