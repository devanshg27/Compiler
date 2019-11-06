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

BooleanLiteral::BooleanLiteral(bool _val) : val(_val) {}
void BooleanLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
BooleanLiteral::~BooleanLiteral() {}

StringLiteral::StringLiteral(std::string _val) : val(_val) {}
void StringLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
StringLiteral::~StringLiteral() {}