#pragma once

#include <bits/stdc++.h>

class AbstractDispatcher;

class Literal {
public:
    Literal();
    virtual void Accept(AbstractDispatcher& dispatcher) = 0;
    ~Literal();
};

class CharacterLiteral : public Literal {
public:
    char val;
    CharacterLiteral(char _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~CharacterLiteral();
};

class IntegerLiteral : public Literal {
public:
    int val;
    IntegerLiteral(int _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~IntegerLiteral();
};

class BooleanLiteral : public Literal {
public:
    bool val;
    BooleanLiteral(bool _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~BooleanLiteral();
};

class StringLiteral : public Literal {
public:
    std::string val;
    StringLiteral(std::string _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~StringLiteral();
};