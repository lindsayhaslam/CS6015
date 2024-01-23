//
// Created by Lindsay Haslam on 1/18/24.
//

#include "Expr.h"
using namespace std;

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

//Var constructor
Var::Var(const string &name){
    this->name = name;
}

bool Var::equals(Expr *e) {
    Var* var = dynamic_cast<Var*>(e);
    if (var) {
        return this->name == var->name;
    }
    return false;
}

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



