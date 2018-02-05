//
// Created by 14667 on 2018/2/4.
//

#ifndef PROGRAMMABLECALCULATOR_FILE_CONTEXT_H
#define PROGRAMMABLECALCULATOR_FILE_CONTEXT_H

#include "symbol-table.h"

namespace ssg {

class Context {
  public:
    Context() { current_symtab = &global_symtab; }

    SymbolTable global_symtab;
    SymbolTable *current_symtab;
};

} // namespace ssg

#endif // PROGRAMMABLECALCULATOR_FILE_CONTEXT_H
