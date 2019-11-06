#include "literal.h"

Literal::Literal() {}
Literal::~Literal() {}

CharacterLiteral::CharacterLiteral(char _val) : val(_val) {}
CharacterLiteral::~CharacterLiteral() {}

IntegerLiteral::IntegerLiteral(int _val) : val(_val) {}
IntegerLiteral::~IntegerLiteral() {}

BooleanLiteral::BooleanLiteral(bool _val) : val(_val) {}
BooleanLiteral::~BooleanLiteral() {}

StringLiteral::StringLiteral(std::string _val) : val(_val) {}
StringLiteral::~StringLiteral() {}