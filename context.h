//
// Created by 14667 on 2018/2/4.
//

#ifndef PROGRAMMABLECALCULATOR_CONTEXT_H
#define PROGRAMMABLECALCULATOR_CONTEXT_H

#include "symbol-table.h"

namespace gss {

class Context {
  public:
    Context() { current_symtab = &global_symtab; }

    bool in_global_scope = true;
    SymbolTable global_symtab;
    SymbolTable *current_symtab;
};

} // namespace gss

#endif // PROGRAMMABLECALCULATOR_CONTEXT_H
