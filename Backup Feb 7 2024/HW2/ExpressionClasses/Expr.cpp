//
// Created by Lindsay Haslam on 1/18/24.
//

#include "Expr.h"
using namespace std;

/****************NUM CLASS****************/
//Num constructor
Num::Num(int val) {
    this->val = val;
}

bool Num::equals(Expr *e) {
    Num* num = dynamic_cast<Num*>(e);
    if (num == nullptr){
        return false;
    }
    else{
        return this->val == num->val;
    }
}

int Num::interp(){
    return val;
}

bool Num::has_variable() {
    return false;
}

Expr* Num::subst( string varName, Expr* replacement) {
    return this;
}

/****************VAR CLASS****************/
//Var constructor
Var::Var( string name){
    this->name = name;
}

bool Var::equals(Expr *e) {
    Var* var = dynamic_cast<Var*>(e);
    if (var) {
        return this->name == var->name;
    }
    return false;
}

int Var::interp(){
    throw std::runtime_error("Variable has no value");
}

bool Var::has_variable(){
    return true;
}

Expr* Var::subst( string varName, Expr* replacement) {
    if (name == varName) {
        return replacement;
    } else {
        //If the variable name does not match, return a new Var instance with the same name.
        return this;
    }
}

/****************ADD CLASS****************/
//Add constructor
Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(Expr *e) {
    Add* add = dynamic_cast<Add*>(e);
    if (add == nullptr){
        return false;
    }
    else {

        return this->lhs->equals(add->lhs) && this->rhs->equals(add->rhs);
    }
}

int Add::interp(){
    return lhs->interp() + rhs->interp();
}

bool Add::has_variable(){
    return lhs->has_variable() || rhs->has_variable();
}
Expr* Add::subst( string varName, Expr* replacement){
    return (new Add(this->lhs->subst(varName, replacement),this->rhs->subst(varName, replacement)));
}

/**************MULT CLASS**************/
//Mult constructor
Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr *e) {
    Mult* mult = dynamic_cast<Mult*>(e);
    if (mult == nullptr){
        return false;
    }
    else {
        return this->lhs->equals(mult->lhs) && this->rhs->equals(mult->rhs);
    }
}

int Mult::interp() {
    return lhs->interp() * rhs->interp();
}

bool Mult::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

Expr* Mult::subst( string varName, Expr* replacement){
    Expr* newLhs = lhs->subst(varName, replacement);
    Expr* newRhs = rhs->subst(varName, replacement);
    return new Mult(newLhs, newRhs);
}




