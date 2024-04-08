//
// Created by Lindsay Haslam on 3/12/24.
//

#include "Val.h"
#include "Expr.h"
#include "pointer.h"

//String Val to String
string Val::to_string(){
    stringstream stream("");
    this->print(stream);
    return stream.str();
}

NumVal::NumVal(int i) {
    val = i;
}

PTR(Expr) NumVal::to_expr() {
    return NEW(Num)(this->val);
}

bool NumVal::equals(PTR(Val) v) {
    //Insert implementation
    PTR(NumVal) numPointer = CAST(NumVal)(v);
    if (numPointer == nullptr){
        return false;
    }
    return this->val == numPointer ->val;
}

PTR(Val) NumVal::add_to(PTR(Val) other_val) {
    //Insert implementation
    PTR(NumVal) other_num = CAST(NumVal)(other_val);
    if (other_num == NULL) throw runtime_error("You can't add a non-number!");
    return NEW(NumVal)(other_num->val + this->val);
}

PTR(Val) NumVal::mult_with(PTR(Val) other_val) {
    //Insert implementation
    PTR(NumVal) other_num = CAST(NumVal)(other_val);
    if(other_num == NULL) throw runtime_error("You can't mult a non-number!");
    return NEW(NumVal)(this->val * other_num->val);
}

void NumVal::print(std::ostream &ostream) {
    ostream <<::to_string(val);
}

//NumVal is_true throws error
void NumVal::is_true(){
    throw runtime_error("Error!");
}

PTR(Val) NumVal::call(PTR(Val) actualArg){
    throw runtime_error("Cannot call NumVal!");
}

//BoolVal
BoolVal::BoolVal(bool b) {
    val = b;
}

PTR(Expr) BoolVal::to_expr() {
    return NEW(BoolExpr)(this->val);
}

bool BoolVal::equals(PTR(Val) v){
    PTR(BoolVal) boolPointer = CAST(BoolVal)(v);

    if (boolPointer == nullptr){
        return false;
    }
    return this-> val == boolPointer->val;
}

PTR(Val) BoolVal::add_to(PTR(Val) other_val) {
    throw runtime_error("Cannot add bool");
}

PTR(Val) BoolVal::mult_with(PTR(Val) other_val) {
    throw runtime_error("Cannot mult bool");
}

void BoolVal::print(ostream &ostream){
    ostream <<::to_string(val);
}

bool BoolVal::is_true(){
    return val;
}

PTR(Val) BoolVal::call(PTR(Val) actualArg){
    throw runtime_error("Cannot call BoolVal");
}

FunVal::FunVal(string formalarg, PTR(Expr) body, PTR(Env) env){
    if (env == nullptr){
        env = Env::empty;
    }
    this->formalarg = formalarg;
    this->body = body;
}

PTR(Expr) FunVal::to_expr(){
    return NEW(FunExpr)(this->formalarg, this->body);
}

bool FunVal::equals (PTR(Val) v){
    PTR(FunVal) funPtr = CAST(FunVal)(v);
    if (funPtr == nullptr){
        return false;
    }
    return this->formalarg == funPtr->formalarg && this->body->equals(funPtr->body);
}

PTR(Val) FunVal::add_to(PTR(Val) other_val) {
    throw runtime_error("Cannot add function!");
}
PTR(Val) FunVal::mult_with(PTR(Val) other_val) {
    throw runtime_error("Cannot multiply function!");
}
void FunVal::print(ostream &ostream){
}

bool FunVal::is_true(){
    return false;
}
PTR(Val) FunVal::call(PTR(Val) actualArg) {
    PTR(Env) newEnv = NEW(ExtendedEnv)(formalarg, actualArg, env);
    // Interpret the body of the function with the extended environment
    return body->interp(newEnv);
}




