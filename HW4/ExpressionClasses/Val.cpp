//
// Created by Lindsay Haslam on 3/12/24.
//

#include "Val.h"
#include "Expr.h"

//String Val to String
string Val::to_string(){
    stringstream stream("");
    this->print(stream);
    return stream.str();
}

NumVal::NumVal(int i) {
    val = i;
}

Expr* NumVal::to_expr() {
    return new Num(this->val);
}

bool NumVal::equals(Val *v) {
    //Insert implementation
    NumVal* numPointer = dynamic_cast<NumVal*>(v);
    if (numPointer == nullptr){
        return false;
    }
    return this->val == numPointer ->val;
}

Val* NumVal::add_to(Val *other_val) {
    //Insert implementation
    NumVal *other_num = dynamic_cast<NumVal*>(other_val);
    if (other_num == NULL) throw runtime_error("You can't add a non-number!");
    return new NumVal(other_num->val + this->val);
}

Val* NumVal::mult_with(Val *other_val) {
    //Insert implementation
    NumVal *other_num = dynamic_cast<NumVal*>(other_val);
    if(other_num == NULL) throw runtime_error("You can't mult a non-number!");
    return new NumVal(this->val * other_num->val);
}

void NumVal::print(std::ostream &ostream) {
    ostream <<::to_string(val);
}

//NumVal is_true throws error
void NumVal::is_true(){
    throw runtime_error("Error!");
}

Val* NumVal::call(Val* actualArg){
    throw runtime_error("Cannot call NumVal!");
}

//BoolVal
BoolVal::BoolVal(bool b) {
    val = b;
}

Expr* BoolVal::to_expr() {
    return new BoolExpr(this->val);
}

bool BoolVal::equals(Val *v){
    BoolVal* boolPointer = dynamic_cast<BoolVal*>(v);

    if (boolPointer == nullptr){
        return false;
    }
    return this-> val == boolPointer->val;
}

Val* BoolVal::add_to(Val* other_val) {
    throw runtime_error("Cannot add bool");
    return new NumVal(-1);
}

Val* BoolVal::mult_with(Val *other_val) {
    throw runtime_error("Cannot mult bool");
    return new NumVal(-1);
}

void BoolVal::print(ostream &ostream){
    ostream <<::to_string(val);
}

bool BoolVal::is_true(){
    return val;
}

Val* BoolVal::call(Val* actualArg){
    throw runtime_error("Cannot call BoolVal");
}

FunVal::FunVal(string formalarg, Expr *body){
    this->formalarg = formalarg;
    this->body = body;
}

Expr* FunVal::to_expr(){
    return new FunExpr(this->formalarg, this->body);
}

bool FunVal::equals (Val *v){
    FunVal* funPtr = dynamic_cast<FunVal*>(v);
    if (funPtr == nullptr){
        return false;
    }
    return this->formalarg == funPtr->formalarg && this->body->equals(funPtr->body);
}

Val* FunVal::add_to(Val *other_val) {
    throw runtime_error("Cannot add function!");
}
Val* FunVal::mult_with(Val *other_val) {
    throw runtime_error("Cannot multiply function!");
}
void FunVal::print(ostream &ostream){
}

bool FunVal::is_true(){
    return false;
}
Val* FunVal::call(Val* actualArg){
    return body->subst(formalarg, actualArg->to_expr())->interp();
}




