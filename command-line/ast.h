//
// Created by 14667 on 2018/2/2.
//

#ifndef PROGRAMMABLECALCULATOR_AST_H
#define PROGRAMMABLECALCULATOR_AST_H

#include <memory>
#include <list>

namespace gss {

class Context;

enum class ExpressionType : int {
    UOP_MINUS,
    UOP_ABS,
    BOP_MUL,
    BOP_DIV,
    BOP_ADD,
    BOP_SUB,
    BOP_ASSIGN,
    BOP_LT,
    BOP_GT,
    BOP_NE,
    BOP_EQ,
    BOP_LE,
    BOP_GE,
};

enum class ControlFlowType : int { IF_THEN, IF_THEN_ELSE, WHILE_DO };

class ASTNode {
  public:
    virtual double eval(Context *) const = 0;

    virtual ~ASTNode() = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;
using ASTNodePtrList = std::list<ASTNodePtr>;

class Expression : public ASTNode {
  public:
    Expression(ExpressionType et, const ASTNodePtr &l, const ASTNodePtr &r)
        : type(et), left(l), right(r) {}

    double eval(Context *) const override;

  private:
    ExpressionType type;
    ASTNodePtr left;
    ASTNodePtr right;
};

class FunctionCall : public ASTNode {
  public:
    FunctionCall(const std::string &fn, const ASTNodePtrList &a) : func_name(fn), args(a) {}

    double eval(Context *) const override;

  private:
    std::string func_name;
    ASTNodePtrList args;
};

class ControlFlow : public ASTNode {
  public:
    ControlFlow(ControlFlowType cft, const ASTNodePtr &c, const ASTNodePtrList &tl,
                const ASTNodePtrList &el)
        : type(cft), condition(c), then_or_do_list(tl), else_list(el) {}

    double eval(Context *) const override;

  private:
    ControlFlowType type;
    ASTNodePtr condition;
    ASTNodePtrList then_or_do_list;
    ASTNodePtrList else_list;
};

class Constant : public ASTNode {
  public:
    Constant(double v) : value(v) {}

    double eval(Context *) const override;

  private:
    double value;
};

class SymbolReference : public ASTNode {
  public:
    SymbolReference(const std::string &sn) : symbol_name(sn) {}

    double eval(Context *) const override;
    const std::string &get_symbol_name() const { return symbol_name; }

  private:
    std::string symbol_name;
};
} // namespace gss

#endif // PROGRAMMABLECALCULATOR_AST_H
