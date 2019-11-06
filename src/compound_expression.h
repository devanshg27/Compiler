#pragma once

#include <bits/stdc++.h>
#include "expression.h"
#include "literal.h"
#include "function_call.h"

class AbstractDispatcher;

class ExpressionLiteral : public Expression {
private:
    Literal* expr;
public:
    ExpressionLiteral(Literal*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~ExpressionLiteral();
};

class ExpressionIdentifier : public Expression {
private:
    std::string id;
    Expression *posx;
    Expression *posy;
public:
    ExpressionIdentifier(std::string);
    ExpressionIdentifier(std::string, Expression*);
    ExpressionIdentifier(std::string, Expression*, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~ExpressionIdentifier();
};

class Binary_op : public Expression {
private:
    Expression* exp1;
    std::string op;
    Expression* exp2;
public:
    Binary_op(Expression*, std::string, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Binary_op();
};

class Unary_op : public Expression {
private:
    std::string op;
    Expression* expr;
public:
    Unary_op(std::string, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Unary_op();
};

class Ternary_op : public Expression {
private:
    Expression* cond;
    Expression* exp1;
    Expression* exp2;
public:
    Ternary_op(Expression*,Expression*,Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Ternary_op();
};

class ExpressionFunctionCall : public Expression {
private:
    Function_call* fcall;
public:
    ExpressionFunctionCall(Function_call*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~ExpressionFunctionCall();
};

class ExpressionBracketed : public Expression {
private:
    Expression* expr;
public:
    ExpressionBracketed(Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~ExpressionBracketed();
};