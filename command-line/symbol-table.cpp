#include "symbol-table.h"

namespace gss {

SymbolTable *global_symtab = nullptr;
SymbolTable *current_symtab = nullptr;

SymbolValue::~SymbolValue() { delete fsymtab; }

void SymbolTable::variable_define(const std::string &name, double value) {
    symtab_[name] = std::make_shared<SymbolValue>(SymbolType::VAR, value);
}

void SymbolTable::function_define(const std::string &name, const ParameterList &params,
                                  SymbolTable *stab, const ASTNodePtrList &body) {
    symtab_[name] = std::make_shared<SymbolValue>(SymbolType::FUNC, params, stab, body);
}

std::optional<SymbolValuePtr> SymbolTable::lookup(const std::string &name) const {
    auto res = symtab_.find(name);
    if (res != symtab_.end()) {
        return std::make_optional<SymbolValuePtr>(res->second);
    }

    return std::optional<SymbolValuePtr>();
}

void SymbolTable::symbol_delete(const std::string &name) {
    auto res = symtab_.find(name);
    if (res != symtab_.cend()) {
        symtab_.erase(res);
    }
}

void SymbolTable::symbol_table_print() const {
    for (const auto &item : symtab_) {
        if (item.second->type == SymbolType::VAR) {
            printf("%-10s variable %4.4f\n", item.first.c_str(), item.second->value);
        } else if (item.second->type == SymbolType::FUNC) {
            printf("%-10s function\n", item.first.c_str());
        } else {
        }
    }
}

} // namespace gss
