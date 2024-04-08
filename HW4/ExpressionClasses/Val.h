//
// Created by Lindsay Haslam on 3/12/24.
//

#ifndef EXPRESSIONCLASSES_VAL_H
#define EXPRESSIONCLASSES_VAL_H

#include <stdio.h>
#include <string>
#include "pointer.h"
#include "Env.h"

using namespace std;
class Expr;

CLASS(Val) {
public:
    virtual bool equals (PTR(Val) v)= 0;
    virtual PTR(Expr) to_expr()= 0;
    virtual PTR(Val) add_to(PTR(Val) other_val) = 0;
    virtual PTR(Val) mult_with(PTR(Val) other_val) = 0;
    virtual void print(ostream &ostream) = 0;
    virtual PTR(Val) call(PTR(Val) actual_arg)=0;
    string to_string();
};

class NumVal : public Val{
public:
    int val;
    NumVal(int i);
    virtual PTR(Expr) to_expr();
    virtual bool equals(PTR(Val) v);
    virtual PTR(Val) add_to(PTR(Val) other_val);
    virtual PTR(Val) mult_with(PTR(Val) other_val);
    virtual void print (ostream &ostream);
    void is_true();
    PTR(Val) call(PTR(Val) actualarg);
};

class BoolVal : public Val {
public:
    bool val;
    BoolVal(bool b);
    virtual PTR(Expr) to_expr();
    virtual bool equals (PTR(Val) v);
    virtual PTR(Val) add_to(PTR(Val) other_val);
    virtual PTR(Val) mult_with(PTR(Val) other_val);
    virtual void print (ostream &ostream);
    virtual bool is_true();
    PTR(Val) call(PTR(Val) actualArg);
};

class FunVal : public Val {
public:
    string formalarg;
    PTR(Expr) body;
    PTR(Env) env;

    FunVal(string formal_arg, PTR(Expr) body, PTR(Env) env = nullptr);
    PTR(Expr) to_expr();
    virtual bool equals (PTR(Val) v);
    virtual PTR(Val) add_to(PTR(Val) other_val);
    virtual PTR(Val) mult_with(PTR(Val) other_val);
    void print(ostream &ostream);
    virtual bool is_true();
    PTR(Val) call(PTR(Val) actualarg);
};

#endif //EXPRESSIONCLASSES_VAL_H
