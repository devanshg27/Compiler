#pragma once

#include <bits/stdc++.h>

class AbstractDispatcher;

class Literal {
private:
public:
    Literal();
    virtual void Accept(AbstractDispatcher& dispatcher) = 0;
    ~Literal();
};

class CharacterLiteral : public Literal {
private:
    char val;
public:
    CharacterLiteral(char _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~CharacterLiteral();
};

class IntegerLiteral : public Literal {
private:
    int val;
public:
    IntegerLiteral(int _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~IntegerLiteral();
};

class BooleanLiteral : public Literal {
private:
    bool val;
public:
    BooleanLiteral(bool _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~BooleanLiteral();
};

class StringLiteral : public Literal {
private:
    std::string val;
public:
    StringLiteral(std::string _val);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~StringLiteral();
};