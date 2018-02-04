#include "symbol-table.h"

namespace gss {

SymbolTable *global_symtab = nullptr;
SymbolTable *current_symtab = nullptr;

SymbolValue::~SymbolValue() { delete fsymtab; }

void SymbolTable::variable_define(const std::string &name, double value) {
    symtab_[name] = std::make_shared<SymbolValue>(SymbolType::VAR, value);
}

void SymbolTable::function_define(const std::string &name, const std::vector<std::string> &params,
                                  SymbolTable *stab,
                                  const std::vector<std::shared_ptr<ASTNode>> &body) {
    symtab_[name] = std::make_shared<SymbolValue>(SymbolType::FUNC, params, stab, body);
}

std::optional<std::shared_ptr<SymbolValue>> SymbolTable::lookup(const std::string &name) const {
    auto res = symtab_.find(name);
    if (res != symtab_.end()) {
        return std::make_optional<std::shared_ptr<SymbolValue>>(res->second);
    }

    return std::optional<std::shared_ptr<SymbolValue>>();
}

void SymbolTable::symbol_delete(const std::string &name) {
    auto res = symtab_.find(name);
    if (res != symtab_.cend()) {
        symtab_.erase(res);
    }
}

} // namespace gss
