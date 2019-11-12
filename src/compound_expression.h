#pragma once

#include <bits/stdc++.h>
#include "expression.h"
#include "literal.h"
#include "function_call.h"

class AbstractDispatcher;

class ExpressionLiteral : public Expression {
public:
    Literal* expr;
    ExpressionLiteral(Literal*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~ExpressionLiteral();
};

class ExpressionIdentifier : public Expression {
public:
    std::string id;
    Expression *posx;
    Expression *posy;
    ExpressionIdentifier(std::string);
    ExpressionIdentifier(std::string, Expression*);
    ExpressionIdentifier(std::string, Expression*, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~ExpressionIdentifier();
};

class Binary_op : public Expression {
public:
    Expression* exp1;
    std::string op;
    Expression* exp2;
    Binary_op(Expression*, std::string, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~Binary_op();
};

class Unary_op : public Expression {
public:
    std::string op;
    Expression* expr;
    Unary_op(std::string, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~Unary_op();
};

class Ternary_op : public Expression {
public:
    Expression* cond;
    Expression* exp1;
    Expression* exp2;
    Ternary_op(Expression*,Expression*,Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~Ternary_op();
};

class ExpressionFunctionCall : public Expression {
public:
    Function_call* fcall;
    ExpressionFunctionCall(Function_call*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~ExpressionFunctionCall();
};

class ExpressionBracketed : public Expression {
public:
    Expression* expr;
    ExpressionBracketed(Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    std::pair<std::string, std::pair<Expression*, Expression*>>* getIdentifier() override;
    ~ExpressionBracketed();
};