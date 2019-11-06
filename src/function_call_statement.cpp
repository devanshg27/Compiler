#include "function_call_statement.h"

Function_call_statement::Function_call_statement(Function_call* _fcall) : fcall(_fcall) {}
Function_call_statement::~Function_call_statement() { delete fcall; }