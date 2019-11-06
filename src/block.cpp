#include "block.h"

Block::Block(Variable_list* _v_list, Statement_list* _s_list) : v_list(_v_list), s_list(_s_list) {}

Block::~Block() {
    if (v_list != NULL)
        delete v_list;
    if (s_list != NULL)
        delete s_list;
}