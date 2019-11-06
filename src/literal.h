#pragma once

#include <bits/stdc++.h>

class Literal {
private:
public:
    Literal();
    ~Literal();
};

class CharacterLiteral : public Literal {
private:
    char val;
public:
    CharacterLiteral(char _val);
    ~CharacterLiteral();
};

class IntegerLiteral : public Literal {
private:
    int val;
public:
    IntegerLiteral(int _val);
    ~IntegerLiteral();
};

class BooleanLiteral : public Literal {
private:
    bool val;
public:
    BooleanLiteral(bool _val);
    ~BooleanLiteral();
};

class StringLiteral : public Literal {
private:
    std::string val;
public:
    StringLiteral(std::string _val);
    ~StringLiteral();
};