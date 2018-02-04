//
// Created by 14667 on 2018/2/2.
//

#ifndef PROGRAMMABLECALCULATOR_SYMBOL_TABLE_H
#define PROGRAMMABLECALCULATOR_SYMBOL_TABLE_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace gss {
enum class SymbolType : int { VAR, FUNC };

class ASTNode;
class SymbolTable;

struct SymbolValue {
  public:
    SymbolValue() = default;
    SymbolValue(SymbolType st, double v) : type(st), value(v) {}
    SymbolValue(SymbolType st, const std::vector<std::string> &params, SymbolTable *stab,
                const std::vector<std::shared_ptr<ASTNode>> &body)
        : type(st), parameters(params), fsymtab(stab), fbody(body) {}
    ~SymbolValue();

  public:
    SymbolType type;
    double value;
    std::vector<std::string> parameters;
    SymbolTable *fsymtab = nullptr;
    std::vector<std::shared_ptr<ASTNode>> fbody;
};

class SymbolTable {
  public:
    void variable_define(const std::string &name, double value);

    void function_define(const std::string &name, const std::vector<std::string> &params,
                         SymbolTable *stab, const std::vector<std::shared_ptr<ASTNode>> &body);

    void symbol_delete(const std::string &name);

    std::optional<std::shared_ptr<SymbolValue>> lookup(const std::string &name) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<SymbolValue>> symtab_;
};

} // namespace gss

#endif // PROGRAMMABLECALCULATOR_SYMBOL_TABLE_H
