#include "program.h"

Program::Program(Variable_list* _v_list, Function_list* _f_list) : v_list(_v_list), f_list(_f_list) {}

Program::~Program() {
    if (v_list != NULL)
        delete v_list;
    if (f_list != NULL)
        delete f_list;
}