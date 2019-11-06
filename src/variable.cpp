#include "variable.h"
#include "visitor.h"

Var_decl::Var_decl(std::string _type, std::string _id, Expression *_init) : type(_type), id(_id), initial_value(_init) {
    shapex = NULL;
    shapey = NULL;
}

Var_decl::Var_decl(std::string _type, std::string _id, int _shapex, Expression *_init) : type(_type), id(_id), initial_value(_init) {
    shapex = new int(_shapex);
    shapey = NULL;
}

Var_decl::Var_decl(std::string _type, std::string _id, int _shapex, int _shapey, Expression *_init) : type(_type), id(_id), initial_value(_init) {
    shapex = new int(_shapex);
    shapey = new int(_shapey);
}

void Var_decl::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}

std::string Var_decl::getType() {
    return type;
}

Var_decl::~Var_decl() {
    if (shapex != NULL)
        delete shapex;
    if (shapey != NULL)
        delete shapey;
}

Multivar_decl::Multivar_decl(Var_decl* decl) {
    decls.push_back(decl);
}

void Multivar_decl::add_var_decl(std::string _id, Expression *_init) {
    decls.push_back(new Var_decl(decls.back()->getType(), _id, _init));
}

void Multivar_decl::add_var_decl(std::string _id, int _shapex, Expression *_init) {
    decls.push_back(new Var_decl(decls.back()->getType(), _id, _shapex, _init));
}

void Multivar_decl::add_var_decl(std::string _id, int _shapex, int _shapey, Expression *_init) {
    decls.push_back(new Var_decl(decls.back()->getType(), _id, _shapex, _shapey, _init));
}

void Multivar_decl::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}

Multivar_decl::~Multivar_decl() {
    for(auto&z: decls) {
        delete z;
    }
}