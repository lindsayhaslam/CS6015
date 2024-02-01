#ifndef EXPRESSIONCLASSES_EXPR_H
#define EXPRESSIONCLASSES_EXPR_H

#include <string>
#include <stdexcept>
using namespace std;

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable()  = 0;
    virtual Expr* subst(string varName, Expr* replacement)  = 0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    //Return the value
    int interp();
    //Num will never have a variable.
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
};

class Var : public Expr{
public:
    string name;
    Var(string name);
    bool equals(Expr *e);
    int interp();
    //Will have a variable.
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
};

class Add : public Expr {
public:
    Expr *lhs, *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    //Sum of the subexpression values
    int interp();
    //Check if either have a variable
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
};

class Mult : public Expr {
public:
    Expr *lhs, *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    //The product of the subexpression values
    int interp();
    //Check if either have a variable
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
};

#endif //EXPRESSIONCLASSES_EXPR_H

