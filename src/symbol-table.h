//
// Created by 14667 on 2018/2/2.
//

#ifndef PROGRAMMABLECALCULATOR_FILE_SYMBOL_TABLE_H
#define PROGRAMMABLECALCULATOR_FILE_SYMBOL_TABLE_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <list>

namespace ssg {
enum class SymbolType : int { VAR, FUNC };

class ASTNode;
class SymbolTable;

using ParameterList = std::list<std::string>;
using ASTNodePtrList = std::list<std::shared_ptr<ASTNode>>;

struct SymbolValue {
  public:
    SymbolValue() = default;
    SymbolValue(SymbolType st, double v) : type(st), value(v) {}
    SymbolValue(SymbolType st, const ParameterList &params, SymbolTable *stab, const ASTNodePtrList &body)
        : type(st), parameters(params), fsymtab(stab), fbody(body) {}
    ~SymbolValue();

  public:
    SymbolType type;
    double value;
    ParameterList parameters;
    SymbolTable *fsymtab = nullptr;
    ASTNodePtrList fbody;
};

using SymbolValuePtr = std::shared_ptr<SymbolValue>;

class SymbolTable {
  public:
    void variable_define(const std::string &name, double value);

    void function_define(const std::string &name, const ParameterList &params, 
    					 SymbolTable *stab, const ASTNodePtrList &body);

    void symbol_delete(const std::string &name);

	void symbol_table_print() const;

    std::optional<SymbolValuePtr> lookup(const std::string &name) const;

  private:
    std::unordered_map<std::string, SymbolValuePtr> symtab_;
};

} // namespace ssg

#endif // PROGRAMMABLECALCULATOR_FILE_SYMBOL_TABLE_H
