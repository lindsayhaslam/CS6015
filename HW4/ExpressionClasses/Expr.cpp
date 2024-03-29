/**
 * \file Expr.cpp
 * \author Lindsay Haslam
 * \date 1/18/24
 * \brief This header file declares the Expr class hierarchy for representing arithmetic expressions.
 * It includes the abstract base class Expr and its derived classes Num, Var, Add, and Mult. Each class implements functionalities for equality comparison, interpretation (evaluation), variable presence checking, substitution, pretty printing, and standard printing of expressions. This architecture allows for the representation and manipulation of complex arithmetic expressions involving numbers, variables, and the operations of addition and multiplication.
 */

#include "Expr.h"
#include "Val.h"

using namespace std;

/***********EXPR CLASS****************/
string Expr::to_string() {
    stringstream st("");
    this->print(st);
    return st.str();
}

void Expr::pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos) {
    print(os);
}

void Expr::pretty_print(ostream &ostream) {
    streampos strmpos = 0;
    pretty_print_at(ostream, prec_none, false, strmpos );
}

string Expr::to_pretty_string() {
    stringstream st("");
    this->pretty_print(st);
    return st.str();
}

/****************NUM CLASS****************/
/**
 * \brief Constructor for Num.
 * \param val The integer value of the Num object.
 * Creates a Num object out of val.
 */
Num::Num(int val) {
    this->val = val;
}

/**
 * \brief Implementation of the equals function for Num.
 * \param e the expression you compare.
 * \return false if num is a null pointer, true otherwise.
 * Verifies the current Num object is equal to a different expression.
 */
bool Num::equals(PTR(Expr) e) {
    //check that other is not null
    if (e != nullptr) {
        PTR(Num) otherNum = CAST(Num)(e);

        //check that otherNum isn't null
        if (otherNum != nullptr) {
            //return if the values are the same or not
            return this->val == otherNum->val;
        }
    }
    return false;
}

/**
 * \brief the interp() function for Num class.
 * \return the integer val of Num object.
 */
PTR(Val) Num::interp() {
    return NEW(NumVal)(val);
}

/**
 * \brief the has_variable() function for Num class.
 *
 * \return ALWAYS will return false.
 * Verifies that there are no variables.
 */
//bool Num::has_variable() {
//    return false;
//}

/**
 * \brief The subst() function for Num.
 * \param varName the variable that will be replaced.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 * Swaps varName with a replacement expression.
 */
PTR(Expr) Num::subst(string varName, PTR(Expr) replacement) {
    return THIS;
}

/**
 * \brief the print function for Num.
 * \param os The output stream to print to.
 * Prints the value of the Num object as a string to the specified output stream.
 */
void Num::print(ostream &os) {
    os << ::to_string(val);
}

/****************VAR CLASS****************/
/**
 * \brief Constructor for Var.
 * \param name The integer value of the Num object.
 * Creates a Num object out of val.
 */
Var::Var(string name) {
    this->name = name;
}

/**
 * \brief Implementation of the equals function for Var.
 * \param e the expression you compare.
 * \return true if name is equal, false otherwise.
 * Verifies the current Var object is equal to a different name.
 */
bool Var::equals(PTR(Expr) e) {
    PTR(Var) var = CAST(Var)(e);
    if (var) {
        return this->name == var->name;
    }
    return false;
}

/**
 * \brief the interp() function for Var class.
 * \return runtime error.
 */
PTR(Val) Var::interp() {
    throw std::runtime_error("Variable has no value");

    return NEW(NumVal)(-1);
}

/**
 * \brief the has_variable() function for Var class.
 *
 * \return ALWAYS will return true.
 * Verifies that a variable is a variable.
 */
//bool Var::has_variable() {
//    return true;
//}

/**
 * \brief The subst() function for Var.
 * \param varName the variable that will be replaced.
 * \param replacement The replacement expression.
 * \return the replacement, or a new Var instance with the same name.
 */
PTR(Expr) Var::subst(string varName, PTR(Expr) replacement) {
    if (name == varName) {
        return replacement;
    } else {
        //If the variable name does not match, return a new Var instance with the same name.
        return CAST(Expr)(THIS);
    }

}

/**
 * \brief the print function for Var.
 * \param ostream The output stream to print to.
 * Prints the value of the Var object to the specified output stream.
 */
void Var::print(ostream &ostream) {
    ostream << name;
}

/****************ADD CLASS****************/
/**
 * \brief Constructor for the Add class.
 * Creates the Add object with left and right expressions.
 * \param lhs The left expression.
 * \param rhs The right expression.
 */
Add::Add(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Implementation of the equals function for Add.
 * \param e the expression you compare.
 * \return false if add is a null pointer, true otherwise.
 * Verifies the current Var object is equal to a different expression.
 */
bool Add::equals(PTR(Expr) e) {
        PTR(Add) otherAdd = CAST(Add)(e);
        if (otherAdd != nullptr && lhs->equals(otherAdd->lhs) && rhs->equals(otherAdd->rhs)){
            return true;
        }
        return false;
}

/**
 * \brief the interp() function for Add class.
 * \return lefthand side and righthand side with the Interp() method.
 */
PTR(Val) Add::interp() {
    return this->lhs->interp()->add_to(this->rhs->interp());
}

/**
 * \brief Checks if the expression contains any variables.
 * \return True if either lhs or rhs contains a variable, false otherwise.
 */
//bool Add::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

/**
 * \brief Substitutes a variable within the expression with another expression.
 * \param varName The name of the variable to be substituted.
 * \param replacement The expression to substitute in place of the variable.
 * \return A new Add expression with the variable substituted.
 */
PTR(Expr) Add::subst(string varName, PTR(Expr) replacement) {
    return NEW(Add)(lhs->subst(varName, replacement), rhs->subst(varName, replacement));
}

/**
 * \brief Prints the Add expression to an output stream.
 * \param ostream The output stream to print to.
 */
void Add::print(ostream &ostream) {
    ostream << "(";
    lhs->print(ostream);
    ostream << " + ";
    rhs->print(ostream);
    ostream << ")";
}

/**
 * \brief Pretty prints the Add expression with correct precedence handling.
 * \param o The output stream to print to.
 * \param prec The precedence level of the expression's context.
 */
void Add::pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos) {
    if (node >= prec_add) {
        os << "(";
    }
    lhs->pretty_print_at(os, prec_add, true, strmpos);
    os << " + ";
    rhs->pretty_print_at(os, prec_none, let_parent, strmpos);
    if (node >= prec_add) {
        os << ")";
    }
}


/**************MULT CLASS**************/
/**
 * \brief Constructor for the Mult class.
 * \param lhs The left-hand side expression of the multiplication.
 * \param rhs The right-hand side expression of the multiplication.
 * Initializes a Mult object with two expressions to be multiplied.
 */
Mult::Mult(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Checks if this Mult expression is equal to another expression.
 * \param e The expression to compare with.
 * \return True if both lhs and rhs of Mult are equal to those of e, false otherwise.
 */
bool Mult::equals(PTR(Expr) e) {
    PTR(Mult) mult = CAST(Mult)(e);
    if (mult == nullptr) {
        return false;
    } else {
        return lhs->equals(mult->lhs) && rhs->equals(mult->rhs);
    }
}

/**
 * \brief Evaluates the multiplication expression.
 * \return The product of the interpretations of lhs and rhs.
 */
PTR(Val) Mult::interp() {
    return this->lhs->interp()->mult_with(this->rhs->interp());
}

/**
 * \brief Checks if the expression contains any variables.
 * \return True if either lhs or rhs contains a variable, false otherwise.
 */
//bool Mult::has_variable() {
//    return lhs->has_variable() || rhs->has_variable();
//}

/**
 * \brief Substitutes a variable within the expression with another expression.
 * \param varName The name of the variable to be substituted.
 * \param replacement The expression to substitute in place of the variable.
 * \return A new Mult expression with the variable substituted.
 */
PTR(Expr) Mult::subst(string varName, PTR(Expr) replacement) {
    PTR(Expr) newLhs = lhs->subst(varName, replacement);
    PTR(Expr) newRhs = rhs->subst(varName, replacement);
    return NEW(Mult)(newLhs, newRhs);
}

/**
 * \brief Prints the Mult expression in a human-readable form.
 * \param ostream The output stream to print to.
 */
void Mult::print(ostream &ostream) {
    ostream << "(";
    this->lhs->print(ostream);
    ostream << " * ";
    this->rhs->print(ostream);
    ostream << ")";
}

/**
 * \brief Pretty prints the Mult expression with appropriate precedence.
  * \param o The output stream to print to.
 * \param prec The current precedence level.
 */
void Mult::pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos) {
    bool pass_paren = let_parent;
    if (node >= prec_mult) {
        os << "(";
        pass_paren = false;
    }
    lhs->pretty_print_at(os, prec_mult, true, strmpos);
    os << " * ";
    rhs->pretty_print_at(os, prec_add, pass_paren, strmpos);
    if (node >= prec_mult) {
        os << ")";
    }
}

///************LET********/
Let::Let(string lhs, PTR(Expr) rhs, PTR(Expr) bodyExpr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->bodyExpr = bodyExpr;
}

//bool Let::has_variable() {
//return rhs->has_variable() || bodyExpr->has_variable();
//}

bool Let::equals(PTR(Expr) e){
    PTR(Let) let = CAST(Let)(e);
    if (let == nullptr) {
        return false;
    } else {
        return this->lhs == let->lhs && this->rhs->equals(let->rhs) && this->bodyExpr->equals(let->bodyExpr);
    }
}

PTR(Val) Let::interp() {
    PTR(Val) rhsValue = rhs->interp();
    return bodyExpr->subst(lhs, rhsValue->to_expr())->interp();
}

PTR(Expr) Let::subst(string varName, PTR(Expr) replacement) {
    //If the variable to be substituted is the same as the current binding, avoid shadowing
    if (lhs == varName) {
        return NEW(Let)(lhs, rhs->subst(varName, replacement), bodyExpr);
    } else {
        //Substitute occurrences of varName in bodyExpr, but avoid capturing the binding
        return NEW(Let)(lhs, rhs->subst(varName, replacement), bodyExpr->subst(varName, replacement));
    }
}

void Let::print(ostream &os) {
    os << "(_let " << lhs << " = ";
    rhs->print(os);
    os << " _in ";
    bodyExpr->print(os);
    os << ")";
}

void Let::pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos){
    //Calculate the indentation based on stream positions

    //Move these two lines underneath the if statement
    streampos currentPos = os.tellp();
    streampos indentSize = currentPos - strmpos;
    if (let_parent) {
        os << "(";
    }

    //Print the "let" part
    //All streampos should go where IndentSize is
    os << "_let " << lhs << " = ";
    rhs->pretty_print_at(os, prec_none, false, indentSize);

    os << "\n ";

    string indentation(indentSize, ' ');

    strmpos = os.tellp();
    //Move to the next line and apply indentation for the "in" part
    os << indentation << " _in  ";

    //Print the body expression with updated strmpos
    bodyExpr->pretty_print_at(os, prec_none, false, strmpos);

    if (let_parent) {
        os << ")";
    }
}

//BoolExpr
BoolExpr::BoolExpr(bool b) {
    this-> val = b;
}

bool BoolExpr::equals(PTR(Expr) e){
    PTR(BoolExpr) boolPointer = CAST(BoolExpr)(e);
    if (boolPointer == nullptr){
        return false;
    }
    return this-> val == boolPointer->val;
}

PTR(Val) BoolExpr::interp() {
    return NEW(BoolVal)(val);
}

//bool BoolExpr::has_variable() {
//    return false;
//}

PTR(Expr) BoolExpr::subst(string str, PTR(Expr) e){
    return THIS;
}

void BoolExpr::print(ostream &ostream){
    if(val){
        ostream << "_true";
    }
    else if (!val){
        ostream << "_false";
    }
}

void BoolExpr::pretty_print_at(ostream &ostream, precedence_t prec, bool let_parent, streampos &strmpos){
    if(val){
        ostream << "_true";
    }
    else if (!val){
        ostream << "_false";
    }
}

//IfExpr
IfExpr::IfExpr(PTR(Expr) if_, PTR(Expr) then_, PTR(Expr) else_){
    this->if_ = if_;
    this->then_ = then_;
    this->else_ = else_;
}

bool IfExpr::equals (PTR(Expr) e) {
    PTR(IfExpr) ifPtr = CAST(IfExpr)(e);

    if (ifPtr == nullptr) {
        //Not the same type, can't be equal
        return false;
    }
    //Check equality by comparing each part of the IfExpr using their equals method
    return this->if_->equals(ifPtr->if_) &&
           this->then_->equals(ifPtr->then_) &&
           this->else_->equals(ifPtr->else_);
}

PTR(Val) IfExpr::interp(){
    PTR(Val) conditionValue = if_->interp();
    PTR(BoolVal) boolCondition = CAST(BoolVal)(conditionValue);
    if (boolCondition != nullptr && boolCondition->is_true()) {
        return then_->interp();
    } else {
        return else_->interp();
    }
}

//bool IfExpr::has_variable(){
//    return this->if_->has_variable()||this->then_->has_variable()||else_->has_variable();
//}

//IS THIS CORRECT?
PTR(Expr) IfExpr::subst(string str, PTR(Expr) e){
    return NEW(IfExpr)(this->if_->subst(str, e),this->then_->subst(str, e), this->else_->subst(str, e));
}

void IfExpr::print(ostream &ostream){
    ostream << "_if ";
    this->if_->print(ostream);
    ostream << "_then ";
    this->then_->print(ostream);
    ostream << "_else ";
    this->else_->print(ostream);
}

void IfExpr::pretty_print_at(ostream &ostream, precedence_t prec, bool let_parent, streampos &strmpos) {

    streampos startPosition = ostream.tellp();

    ostream << "_if ";

    if_->pretty_print_at(ostream, prec_none, false, strmpos);

    ostream << "\n";

    strmpos = ostream.tellp();

    ostream << "_then ";

    then_->pretty_print_at(ostream, prec_none, false, strmpos);

    ostream << "\n";

    ostream << "_else ";

    strmpos = ostream.tellp();

    else_->pretty_print_at(ostream, prec_none, false, strmpos);

    ostream << "\n";

}

//EqExpr

EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals (PTR(Expr) e){
    PTR(EqExpr) eqPtr = CAST(EqExpr)(e);

    if (eqPtr == nullptr) {
        return false;
    }
    return this->rhs->equals(eqPtr->rhs) && this->lhs->equals(eqPtr->lhs);
}

PTR(Val) EqExpr::interp(){
    return NEW(BoolVal)(rhs->interp()->equals(lhs->interp()));
}

//bool EqExpr::has_variable(){
//    return this->rhs->has_variable()||this->lhs->has_variable();
//}

PTR(Expr) EqExpr::subst(string str, PTR(Expr) e){
    return NEW(EqExpr)(this->rhs->subst(str, e), this->lhs->subst(str, e));
}

void EqExpr::print(ostream &ostream){
    this->lhs->print(ostream);
    ostream << "==";
    this->rhs->print(ostream);
}

void EqExpr::pretty_print_at(ostream &ostream, precedence_t prec, bool let_parent, streampos &strmpos){
    streampos startPosition = ostream.tellp();

    lhs->pretty_print_at(ostream, prec_none, false, strmpos);
    ostream << "==";
    rhs->pretty_print_at(ostream, prec_none, false, strmpos);
}

//FUNEXPR SECTION
FunExpr::FunExpr(string formalarg, PTR(Expr) body){
    this->formalarg = formalarg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr) e) {
    PTR(FunExpr) funPtr = CAST(FunExpr)(e);
    if (funPtr == nullptr){
        return false;
    }
    return this->formalarg == funPtr->formalarg && this->body->equals(funPtr->body);
}

PTR(Val) FunExpr::interp() {
    return NEW(FunVal)(formalarg, body);
}

PTR(Expr) FunExpr::subst(string str, PTR(Expr) e){
    if(formalarg == str){
        return THIS;
    }
    else {
        return NEW(FunExpr)(formalarg, body->subst(str, e));
    }
}

void FunExpr::print(ostream& o){
    o << "(_fun (" << this->formalarg << ") " << this->body->to_string() << ")";
}

//CALLEXPR SECTION
CallExpr::CallExpr(PTR(Expr) toBeCalled, PTR(Expr) actualArg){
    this->toBeCalled = toBeCalled;
    this->actualArg = actualArg;
};

bool CallExpr::equals(PTR(Expr) e){
    PTR(CallExpr) callPtr = CAST(CallExpr)(e);
    if (callPtr == nullptr){
        return false;
    }
    return this->toBeCalled->equals(callPtr->toBeCalled) && this->actualArg->equals(callPtr->actualArg);
}
PTR(Val) CallExpr::interp(){
    return this->toBeCalled->interp()->call(actualArg->interp());
}
PTR(Expr) CallExpr::subst(string str, PTR(Expr) e){
    return NEW(CallExpr)(this->toBeCalled->subst(str, e), this->actualArg->subst(str, e));
}
void CallExpr::print(ostream &ostream){
    ostream << "(" << this->toBeCalled->to_string() << ") (" << this->actualArg->to_string() << ")";
}


