//
// Created by Lindsay Haslam on 3/12/24.
//

#ifndef EXPRESSIONCLASSES_VAL_H
#define EXPRESSIONCLASSES_VAL_H

#include <stdio.h>
#include <string>

using namespace std;
class Expr;

class Val {
public:
    virtual bool equals (Val *v)= 0;
    virtual Expr* to_expr()= 0;
    virtual Val* add_to(Val* other_val) = 0;
    virtual Val* mult_with(Val* other_val) = 0;
    virtual void print(ostream &ostream) = 0;
    string to_string();
};

class NumVal : public Val{
public:
    int val;
    NumVal(int i);
    virtual Expr* to_expr();
    virtual bool equals (Val *v);
    virtual Val* add_to(Val* other_val);
    virtual Val* mult_with(Val* other_val);
    virtual void print (ostream &ostream);
    virtual Val* is_true();
};

class BoolVal : public Val {
public:
    bool val;
    BoolVal(bool b);
    virtual Expr* to_expr();
    virtual bool equals (Val *v);
    virtual Val* add_to(Val* other_val);
    virtual Val* mult_with(Val* other_val);
    virtual void print (ostream &ostream);
    virtual bool is_true();
};


#endif //EXPRESSIONCLASSES_VAL_H
