/**
 * \file Expr.cpp
 * \author Lindsay Haslam
 * \date 1/18/24
 * \brief This header file declares the Expr class hierarchy for representing arithmetic expressions.
 * It includes the abstract base class Expr and its derived classes Num, Var, Add, and Mult. Each class implements functionalities for equality comparison, interpretation (evaluation), variable presence checking, substitution, pretty printing, and standard printing of expressions. This architecture allows for the representation and manipulation of complex arithmetic expressions involving numbers, variables, and the operations of addition and multiplication.
 */

#include "Expr.h"
#include "Val.h"

//using namespace std;

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
bool Num::equals(Expr *e) {
    Num *num = dynamic_cast<Num *>(e);
    if (num == nullptr) {
        return false;
    } else {
        return this->val == num->val;
    }
}

/**
 * \brief the interp() function for Num class.
 * \return the integer val of Num object.
 */
Val* Num::interp() {
    return new NumVal(val);
}

/**
 * \brief the has_variable() function for Num class.
 *
 * \return ALWAYS will return false.
 * Verifies that there are no variables.
 */
bool Num::has_variable() {
    return false;
}

/**
 * \brief The subst() function for Num.
 * \param varName the variable that will be replaced.
 * \param replacement The replacement expression.
 * \return The new expression with the variable substituted.
 * Swaps varName with a replacement expression.
 */
Expr *Num::subst(string varName, Expr *replacement) {
    return this;
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
bool Var::equals(Expr *e) {
    Var *var = dynamic_cast<Var *>(e);
    if (var) {
        return this->name == var->name;
    }
    return false;
}

/**
 * \brief the interp() function for Var class.
 * \return runtime error.
 */
Val* Var::interp() {
    throw std::runtime_error("Variable has no value");

    return new NumVal(-1);
}

/**
 * \brief the has_variable() function for Var class.
 *
 * \return ALWAYS will return true.
 * Verifies that a variable is a variable.
 */
bool Var::has_variable() {
    return true;
}

/**
 * \brief The subst() function for Var.
 * \param varName the variable that will be replaced.
 * \param replacement The replacement expression.
 * \return the replacement, or a new Var instance with the same name.
 */
Expr *Var::subst(string varName, Expr *replacement) {
    if (name == varName) {
        return replacement;
    } else {
        //If the variable name does not match, return a new Var instance with the same name.
        return this;
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
Add::Add(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Implementation of the equals function for Add.
 * \param e the expression you compare.
 * \return false if add is a null pointer, true otherwise.
 * Verifies the current Var object is equal to a different expression.
 */
bool Add::equals(Expr *e) {
    Add *add = dynamic_cast<Add *>(e);
    if (add == nullptr) {
        return false;
    } else {
        return this->lhs->equals(add->lhs) && this->rhs->equals(add->rhs);
    }
}

/**
 * \brief the interp() function for Add class.
 * \return lefthand side and righthand side with the Interp() method.
 */
Val* Add::interp() {
    return this->lhs->interp()->add_to(this->rhs->interp());
}

/**
 * \brief Checks if the expression contains any variables.
 * \return True if either lhs or rhs contains a variable, false otherwise.
 */
bool Add::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

/**
 * \brief Substitutes a variable within the expression with another expression.
 * \param varName The name of the variable to be substituted.
 * \param replacement The expression to substitute in place of the variable.
 * \return A new Add expression with the variable substituted.
 */
Expr *Add::subst(string varName, Expr *replacement) {
    return (new Add(this->lhs->subst(varName, replacement), this->rhs->subst(varName, replacement)));
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
Mult::Mult(Expr *lhs, Expr *rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

/**
 * \brief Checks if this Mult expression is equal to another expression.
 * \param e The expression to compare with.
 * \return True if both lhs and rhs of Mult are equal to those of e, false otherwise.
 */
bool Mult::equals(Expr *e) {
    Mult *mult = dynamic_cast<Mult *>(e);
    if (mult == nullptr) {
        return false;
    } else {
        return this->lhs->equals(mult->lhs) && this->rhs->equals(mult->rhs);
    }
}

/**
 * \brief Evaluates the multiplication expression.
 * \return The product of the interpretations of lhs and rhs.
 */
Val* Mult::interp() {
    return this->lhs->interp()->mult_with(this->rhs->interp());
}

/**
 * \brief Checks if the expression contains any variables.
 * \return True if either lhs or rhs contains a variable, false otherwise.
 */
bool Mult::has_variable() {
    return lhs->has_variable() || rhs->has_variable();
}

/**
 * \brief Substitutes a variable within the expression with another expression.
 * \param varName The name of the variable to be substituted.
 * \param replacement The expression to substitute in place of the variable.
 * \return A new Mult expression with the variable substituted.
 */
Expr *Mult::subst(string varName, Expr *replacement) {
    Expr *newLhs = lhs->subst(varName, replacement);
    Expr *newRhs = rhs->subst(varName, replacement);
    return new Mult(newLhs, newRhs);
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
Let::Let(string lhs, Expr* rhs, Expr* bodyExpr){
    this->lhs = lhs;
    this->rhs = rhs;
    this->bodyExpr = bodyExpr;
}

bool Let::has_variable() {
return rhs->has_variable() || bodyExpr->has_variable();
}

bool Let::equals(Expr *e){
    Let *let = dynamic_cast<Let *>(e);
    if (let == nullptr) {
        return false;
    } else {
        return this->lhs == let->lhs && this->rhs->equals(let->rhs) && this->bodyExpr->equals(let->bodyExpr);
    }
}

Val* Let::interp() {
    Val* rhsValue = rhs->interp();
    return bodyExpr->subst(lhs, rhsValue->to_expr())->interp();
}

Expr *Let::subst(string varName, Expr *replacement) {
    //If the variable to be substituted is the same as the current binding, avoid shadowing
    if (lhs == varName) {
        return new Let(lhs, rhs->subst(varName, replacement), bodyExpr);
    } else {
        //Substitute occurrences of varName in bodyExpr, but avoid capturing the binding
        return new Let(lhs, rhs->subst(varName, replacement), bodyExpr->subst(varName, replacement));
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