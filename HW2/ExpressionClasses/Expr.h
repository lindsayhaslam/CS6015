#ifndef EXPRESSIONCLASSES_EXPR_H
#define EXPRESSIONCLASSES_EXPR_H

#include <string>
using namespace std;

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
};

class Var : public Expr{
public:
    string name;
    Var(const string &name);
    bool equals(Expr *e);
};

class Add : public Expr {
public:
    Expr *lhs, *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
};

class Mult : public Expr {
public:
    Expr *lhs, *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
};

#endif //EXPRESSIONCLASSES_EXPR_H

