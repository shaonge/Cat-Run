//
// Created by 14667 on 2018/2/3.
//

#include "ast.h"
#include "context.h"
#include "error.h"

namespace gss {

double Expression::eval(Context *c) const {
    double v = 0;
    switch (type) {
    case ExpressionType::UOP_ABS:
        v = abs(left->eval(c));
        break;
    case ExpressionType::UOP_MINUS:
        v = -(left->eval(c));
        break;
    case ExpressionType::BOP_ADD:
        v = left->eval(c) + right->eval(c);
        break;
    case ExpressionType::BOP_SUB:
        v = left->eval(c) - right->eval(c);
        break;
    case ExpressionType::BOP_MUL:
        v = left->eval(c) * right->eval(c);
        break;
    case ExpressionType::BOP_DIV:
        v = left->eval(c) / right->eval(c);
        break;
    case ExpressionType::BOP_ASSIGN:
        v = right->eval(c);
        c->current_symtab->variable_define(
            dynamic_cast<SymbolReference *>(left.get())->get_symbol_name(), v);
        break;
    case ExpressionType::BOP_LT:
        v = (left->eval(c) < right->eval(c));
        break;
    case ExpressionType::BOP_LE:
        v = (left->eval(c) <= right->eval(c));
        break;
    case ExpressionType::BOP_GT:
        v = (left->eval(c) > right->eval(c));
        break;
    case ExpressionType::BOP_GE:
        v = (left->eval(c) >= right->eval(c));
        break;
    case ExpressionType::BOP_EQ:
        v = (left->eval(c) == right->eval(c));
        break;
    case ExpressionType::BOP_NE:
        v = (left->eval(c) != right->eval(c));
        break;
    }

    return v;
}

double FunctionCall::eval(Context *c) const {
    auto res = c->current_symtab->lookup(func_name);
    if (!res) {
        runtime_error("undefined symbol: ", func_name);
    } else if ((*res)->type == SymbolType::VAR) {
        runtime_error("referenced symbol is not a function\n");
    } else if ((*res)->parameters.size() != args.size()) {
        runtime_error("arguments is too many or less\n");
    } else {
    }

    c->current_symtab = (*res)->fsymtab;

    auto piter = (*res)->parameters.cbegin(), pend = (*res)->parameters.cend();
    auto aiter = args.cbegin(), aend = args.cend();
    for (; aiter != aend && piter != pend; ++aiter, ++piter) {
        c->current_symtab->variable_define(*piter, (*aiter)->eval(c));
    }

    double v = 0;
    for (auto iter = (*res)->fbody.cbegin(), end = (*res)->fbody.cend(); iter != end; ++iter) {
        v = (*iter)->eval(c);
    }

    c->current_symtab = &(c->global_symtab);

    return v;
}

double ControlFlow::eval(Context *c) const {
    double v = 0;
    switch (type) {
    case ControlFlowType::IF_THEN:
        if (condition->eval(c)) {
            for (auto iter = then_or_do_list.cbegin(), end = then_or_do_list.cend(); iter != end;
                 ++iter) {
                v = (*iter)->eval(c);
            }
        }
        break;
    case ControlFlowType::IF_THEN_ELSE:
        if (condition->eval(c)) {
            for (auto iter = then_or_do_list.cbegin(), end = then_or_do_list.cend(); iter != end;
                 ++iter) {
                v = (*iter)->eval(c);
            }
        } else {
            for (auto iter = else_list.cbegin(), end = else_list.cend(); iter != end; ++iter) {
                v = (*iter)->eval(c);
            }
        }
        break;
    case ControlFlowType::WHILE_DO:
        while (condition->eval(c)) {
            for (auto iter = then_or_do_list.cbegin(), end = then_or_do_list.cend(); iter != end;
                 ++iter) {
                v = (*iter)->eval(c);
            }
        }
        break;
    }

    return v;
}

double Constant::eval(Context *c) const { return value; }

double SymbolReference::eval(Context *c) const {
    auto res = c->current_symtab->lookup(symbol_name);
    if (!res) {
        runtime_error("undefined symbol: ", symbol_name);
    } else if ((*res)->type == SymbolType::FUNC) {
        runtime_error("referenced symbol is a function\n");
    } else {
    }

    return (*res)->value;
}
} // namespace gss
