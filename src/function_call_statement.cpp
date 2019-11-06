#include "function_call_statement.h"
#include "visitor.h"

Function_call_statement::Function_call_statement(Function_call* _fcall) : fcall(_fcall) {}
void Function_call_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
Function_call_statement::~Function_call_statement() { delete fcall; }