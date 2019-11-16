#include "literal.h"
#include "visitor.h"

Literal::Literal() {}
Literal::~Literal() {}

CharacterLiteral::CharacterLiteral(char _val) : val(_val) {}
void CharacterLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
CharacterLiteral::~CharacterLiteral() {}

IntegerLiteral::IntegerLiteral(int _val) : val(_val) {}
void IntegerLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
IntegerLiteral::~IntegerLiteral() {}

UnsignedLiteral::UnsignedLiteral(unsigned _val) : val(_val) {}
void UnsignedLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
UnsignedLiteral::~UnsignedLiteral() {}

BooleanLiteral::BooleanLiteral(bool _val) : val(_val) {}
void BooleanLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
BooleanLiteral::~BooleanLiteral() {}

StringLiteral::StringLiteral(std::string _val) {
    val = "";
    for(int i=0; i<(int)_val.length(); ++i) {
        if(_val[i] != '\\') val += _val[i];
        else if(_val[i+1] == 'n') {
            val += '\n';
            ++i;
        }
        else if(_val[i+1] == 't') {
            val += '\t';
            ++i;
        }
        else if(_val[i+1] == '\'') {
            val += '\'';
            ++i;
        }
        else if(_val[i+1] == '\\') {
            val += '\\';
            ++i;
        }
        else if(_val[i+1] == '\"') {
            val += '\"';
            ++i;
        }
        else if(_val[i+1] == 'r') {
            val += '\r';
            ++i;
        }
        else {
            assert(0);
        }
    }
}
void StringLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
StringLiteral::~StringLiteral() {}