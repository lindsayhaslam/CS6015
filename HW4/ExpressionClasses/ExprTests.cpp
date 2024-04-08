/**
 * \file ExprTests.cpp
 * \author Lindsay Haslam
 * \date 1/18/24
 * \brief This test file contains a series of test cases for the Expr class hierarchy, focusing on Var, Num, Add, and Mult classes.
 *
 * It includes tests for equality checks, interpretation (evaluation), variable presence checks, substitution, and pretty printing functionalities of arithmetic expressions. Each test case is designed to verify the correct behavior of the classes and their interactions, ensuring that expressions are correctly manipulated and evaluated according to the rules of arithmetic and variable substitution.
 */
#include "catch.h"
#include "Expr.h"
#include "Val.h"
#include "parse.hpp"
#include "pointer.h"


//**********VAR TESTS********//
TEST_CASE("Expr Var") {
    //Test with same name
    CHECK((NEW(Var)("x"))->equals(NEW(Var)("x")) == true );
    //Test with different name
    CHECK((NEW(Var)("x"))->equals(NEW(Var)("y")) == false);
    //Test comparing Var with a Num
    CHECK((NEW(Var)("z"))->equals(NEW(Num)(1)) == false);
    //Testing interp
    CHECK_THROWS_WITH((NEW(Var)("x"))->interp(Env::empty), "Variable has no value");
}

TEST_CASE("Var Interp Throws") {
    CHECK_THROWS_AS((NEW(Var)("x"))->interp(Env::empty), std::runtime_error);
    CHECK_THROWS_WITH((NEW(Var)("x"))->interp(Env::empty), "Variable has no value");
}

//TEST_CASE("Var Has Variable") {
//    CHECK((NEW(Var)("x"))->has_variable());
//    CHECK((NEW(Var)("anything"))->has_variable());
//    //Even if the name is numeric, it's still a variable
//    CHECK((NEW(Var)("123"))->has_variable());
//}

/**Subst Test: Removed**/
//TEST_CASE("Var Subst") {
//    //Substitution matches the variable name
//    CHECK((NEW(Var)("x"))->subst("x", NEW(Num)(5))->equals(NEW(Num)(5)));
//    //Substitution does not match the variable name, no substitution occurs
//    auto noSubstExpr = (NEW(Var)("x"))->subst("y", NEW(Num)(5));
//    CHECK(noSubstExpr->equals(NEW(Var)("x")));
//    //Substitution with another variable
//    CHECK((NEW(Var)("x"))->subst("x", NEW(Var)("y"))->equals(NEW(Var)("y")));
//    // Substitution with a complex expression
//    CHECK((NEW(Var)("x"))->subst("x", NEW(Add)(NEW(Num)(1), NEW(Num)(2)))->equals(NEW(Add)(NEW(Num)(1), NEW(Num)(2))));
//    // No substitution when variable names do not match
//    auto noMatchSubst = (NEW(Var)("x"))->subst("z", NEW(Num)(10));
//    CHECK(noMatchSubst->equals(NEW(Var)("x")));
//}


//**********ADD TESTS********//
TEST_CASE("Expr Add") {
    //Same operands
    CHECK((NEW(Add)(NEW(Num)(2), NEW(Num)(3)))->equals(NEW(Add)(NEW(Num)(2), NEW(Num)(3))) == true);
    //Different operands
    CHECK((NEW(Add)(NEW(Num)(2), NEW(Num)(3)))->equals(NEW(Add)(NEW(Num)(3), NEW(Num)(2))) == false);
    //Test comparing Add with a Var
    CHECK((NEW(Add)(NEW(Num)(1), NEW(Num)(2)))->equals(NEW(Var)("x")) == false);
    //Test with both operands being negative
    CHECK((NEW(Add)(NEW(Num)(-2), NEW(Num)(-3)))->equals(NEW(Add)(NEW(Num)(-2), NEW(Num)(-3))) == true);
    //Test with one operand being negative
    CHECK((NEW(Add)(NEW(Num)(2), NEW(Num)(-3)))->equals(NEW(Add)(NEW(Num)(2), NEW(Num)(-3))) == true);
    //Test from HW3
    CHECK((NEW(Add)(NEW(Add)(NEW(Num)(100), NEW(Num)(100)), NEW(Add)(NEW(Num)(200),NEW(Num)(200))))->interp(Env::empty)->equals(NEW(NumVal)(600)));
}

TEST_CASE("Add Interp") {
    CHECK((NEW(Add)(NEW(Num)(3), NEW(Num)(2)))->interp(Env::empty)->equals(NEW(NumVal)(5)));
    CHECK((NEW(Add)(NEW(Num)(5), NEW(Num)(-4)))->interp(Env::empty)->equals(NEW(NumVal)(1)));
    CHECK((NEW(Add)(NEW(Num)(-3), NEW(Num)(3)))->interp(Env::empty)->equals(NEW(NumVal)(0)));
    CHECK((NEW(Add)(NEW(Num)(-3), NEW(Num)(-3)))->interp(Env::empty)->equals(NEW(NumVal)(-6)));
    CHECK((NEW(Add)(NEW(Num)(0), NEW(Num)(10)))->interp(Env::empty)->equals(NEW(NumVal)(10)));
}

//TEST_CASE("Add Has Variable") {
//    CHECK_FALSE((NEW(Add)(NEW(Num)(5), NEW(Num)(4)))->has_variable());
//    CHECK_FALSE((NEW(Add)(NEW(Num)(0), NEW(Num)(-4)))->has_variable());
//    CHECK((NEW(Add)(NEW(Var)("x"), NEW(Num)(4)))->has_variable());
//    CHECK((NEW(Add)(NEW(Num)(4), NEW(Var)("y")))->has_variable());
//    CHECK((NEW(Add)(NEW(Var)("x"), NEW(Var)("y")))->has_variable());
//}

/**Subst Test: Removed**/
//TEST_CASE("Add Subst") {
//    CHECK((NEW(Add)(NEW(Var)("x"), NEW(Num)(3)))->subst("x", NEW(Num)(5))->interp()->equals(NEW(NumVal)(8)));
//    CHECK((NEW(Add)(NEW(Num)(3), NEW(Var)("x")))->subst("x", NEW(Num)(2))->interp()->equals(NEW(NumVal)(5)));
//    CHECK((NEW(Add)(NEW(Num)(-1), NEW(Var)("x")))->subst("x", NEW(Num)(2))->interp()->equals(NEW(NumVal)( 1)));
//    CHECK((NEW(Add)(NEW(Var)("x"), NEW(Var)("x")))->subst("x", NEW(Num)(3))->interp()->equals(NEW(NumVal)(6)));
//    CHECK((NEW(Add)(NEW(Var)("y"), NEW(Var)("z")))->subst("y", NEW(Num)(3))->subst("z", NEW(Num)(2))->interp()->equals(NEW(NumVal)(5)));
//}


//**********NUM TESTS********//
TEST_CASE("Expr Num") {
    //Check that different expressions are unequal
    CHECK((NEW(Num)(1))->equals(NEW(Var)("x")) == false);
    //Check with nullpointer
    CHECK((NEW(Num)(7))->equals(nullptr) == false);
    //Check itself
    PTR(Expr) sameNum = NEW(Num)(8);
    CHECK(sameNum->equals(sameNum) == true);
    //Check two Num objects with different negative numbers
    CHECK((NEW(Num)(-3))->equals(NEW(Num)(-4)) == false);
    //Check a Num object with a negative number against a positive number
    CHECK((NEW(Num)(-2))->equals(NEW(Num)(2)) == false);
}

TEST_CASE("Num Interp") {
    CHECK((NEW(Num)(3))->interp(Env::empty)->equals(NEW(NumVal)(3)));
    CHECK((NEW(Num)(5))->interp(Env::empty)->equals(NEW(NumVal)(5)));
    CHECK((NEW(Num)(-18))->interp(Env::empty)->equals(NEW(NumVal)(-18)));
    CHECK((NEW(Num)(-3))->interp(Env::empty)->equals(NEW(NumVal)(-3)));
    CHECK((NEW(Num)(0))->interp(Env::empty)->equals(NEW(NumVal)(0)));
}

//TEST_CASE("Num Has Variable") {
//    CHECK_FALSE((NEW(Num)(5))->has_variable());
//    CHECK_FALSE((NEW(Num)(0))->has_variable());
//    CHECK_FALSE((NEW(Num)(-20))->has_variable());
//    CHECK_FALSE((NEW(Num)(4))->has_variable());
//    CHECK_FALSE((NEW(Num)(1000))->has_variable());
//}

//**********MULT TESTS********//
TEST_CASE("Expr Mult") {
    //Identical multiplication expressions
    CHECK((NEW(Mult)(NEW(Num)(2), NEW(Num)(3)))->equals(NEW(Mult)(NEW(Num)(2), NEW(Num)(3))) == true);
    //Different multiplication expressions
    CHECK((NEW(Mult)(NEW(Num)(2), NEW(Num)(3)))->equals(NEW(Mult)(NEW(Num)(3), NEW(Num)(2))) == false);
    //Test equality with more complex nested expressions
    CHECK((NEW(Mult)(NEW(Add)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(3)))->equals(
            NEW(Mult)(NEW(Add)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(3))) == true);
    //Test with different operands (one negative)
    CHECK((NEW(Mult)(NEW(Num)(-8), NEW(Num)(9)))->equals(NEW(Mult)(NEW(Num)(9), NEW(Num)(-8))) == false);
    //Test with a negative number in a nested expression
    CHECK((NEW(Mult)(NEW(Add)(NEW(Num)(-1), NEW(Num)(2)), NEW(Num)(3)))->equals(
            NEW(Mult)(NEW(Add)(NEW(Num)(-1), NEW(Num)(2)), NEW(Num)(3))) == true);

}

TEST_CASE("Mult Interp") {
    CHECK((NEW(Mult)(NEW(Num)(3), NEW(Num)(2)))->interp(Env::empty)->equals(NEW(NumVal)(6)));
    CHECK((NEW(Mult)(NEW(Num)(5), NEW(Num)(4)))->interp(Env::empty)->equals(NEW(NumVal)(20)));
    CHECK((NEW(Mult)(NEW(Num)(-3), NEW(Num)(6)))->interp(Env::empty)->equals(NEW(NumVal)(-18)));
    CHECK((NEW(Mult)(NEW(Num)(-3), NEW(Num)(-3)))->interp(Env::empty)->equals(NEW(NumVal)(9)));
    CHECK((NEW(Mult)(NEW(Num)(0), NEW(Num)(10)))->interp(Env::empty)->equals(NEW(NumVal)(0)));
}

//TEST_CASE("Mult Has Variable") {
//    CHECK_FALSE((NEW(Mult)(NEW(Num)(5), NEW(Num)(4)))->has_variable());
//    CHECK_FALSE((NEW(Mult)(NEW(Num)(0), NEW(Num)(-4)))->has_variable());
//    CHECK((NEW(Mult)(NEW(Var)("x"), NEW(Num)(4)))->has_variable());
//    CHECK((NEW(Mult)(NEW(Num)(4), NEW(Var)("y")))->has_variable());
//    CHECK((NEW(Mult)(NEW(Var)("x"), NEW(Var)("y")))->has_variable());
//}

/**Subst Test: Removed**/
//TEST_CASE("Mult Subst") {
//    CHECK((NEW(Mult)(NEW(Var)("x"), NEW(Num)(3)))->subst("x", NEW(Num)(5))->interp()->equals(NEW(NumVal)(15)));
//    CHECK((NEW(Mult)(NEW(Num)(3), NEW(Var)("x")))->subst("x", NEW(Num)(2))->interp()->equals(NEW(NumVal)(6)));
//    CHECK((NEW(Mult)(NEW(Num)(-1), NEW(Var)("x")))->subst("x", NEW(Num)(2))->interp()->equals(NEW(NumVal)(-2)));
//    CHECK((NEW(Mult)(NEW(Var)("x"), NEW(Var)("x")))->subst("x", NEW(Num)(3))->interp()->equals(NEW(NumVal)(9)));
//    CHECK((NEW(Mult)(NEW(Var)("y"), NEW(Var)("z")))->subst("y", NEW(Num)(3))->subst("z", NEW(Num)(2))->interp()->equals(NEW(NumVal)(6)));
//}


/****PRETTY PRINT TESTS*****/
TEST_CASE("Nabil's Tests for Pretty Print") {
    CHECK ((NEW(Mult)(NEW(Num)(1), NEW(Add)(NEW(Num)(2), NEW(Num)(3))))->to_pretty_string() == "1 * (2 + 3)");
    CHECK ((NEW(Mult)(NEW(Mult)(NEW(Num)(8), NEW(Num)(1)), NEW(Var)("y")))->to_pretty_string() == "(8 * 1) * y");
    CHECK ((NEW(Mult)(NEW(Add)(NEW(Num)(3), NEW(Num)(5)), NEW(Mult)(NEW(Num)(6), NEW(Num)(1))))->to_pretty_string() ==
           "(3 + 5) * 6 * 1");
    CHECK ((NEW(Mult)(NEW(Mult)(NEW(Num)(7), NEW(Num)(7)), NEW(Add)(NEW(Num)(9), NEW(Num)(2))))->to_pretty_string() ==
           "(7 * 7) * (9 + 2)");
}

TEST_CASE("Pretty Print Mult Expressions") {
    //Mult within Mult
    CHECK((NEW(Mult)(NEW(Mult)(NEW(Num)(2), NEW(Num)(3)), NEW(Num)(4)))->to_pretty_string() == "(2 * 3) * 4");
    //Mult within Mult (negative numbers)
    CHECK((NEW(Mult)(NEW(Mult)(NEW(Num)(-1), NEW(Num)(-3)), NEW(Num)(6)))->to_pretty_string() == "(-1 * -3) * 6");
    //Add within Mult
    CHECK((NEW(Mult)(NEW(Add)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(3)))->to_pretty_string() == "(1 + 2) * 3");
    //Add within Mult (negative numbers)
    CHECK((NEW(Mult)(NEW(Add)(NEW(Num)(-4), NEW(Num)(1)), NEW(Num)(5)))->to_pretty_string() == "(-4 + 1) * 5");
    //Deeply Nested
    CHECK((NEW(Mult)(NEW(Add)(NEW(Mult)(NEW(Num)(2), NEW(Var)("x")), NEW(Num)(3)),
                    NEW(Add)(NEW(Num)(4), NEW(Var)("y"))))->to_pretty_string() == "(2 * x + 3) * (4 + y)");

}

TEST_CASE("Pretty Print Add Expressions") {
    //Add within Add
    CHECK((NEW(Add)(NEW(Add)(NEW(Num)(1), NEW(Num)(2)), NEW(Num)(3)))->to_pretty_string() == "(1 + 2) + 3");
    //Mult within Add
    CHECK((NEW(Add)(NEW(Num)(1), NEW(Mult)(NEW(Num)(2), NEW(Num)(3))))->to_pretty_string() == "1 + 2 * 3");
    //Nested expressions
    CHECK((NEW(Add)(NEW(Mult)(NEW(Num)(1), NEW(Add)(NEW(Num)(2), NEW(Num)(3))), NEW(Num)(4)))->to_pretty_string() ==
          "1 * (2 + 3) + 4");
    //Nested with Variables
    CHECK((NEW(Add)(NEW(Var)("x"), NEW(Mult)(NEW(Var)("y"), NEW(Add)(NEW(Num)(1), NEW(Num)(2)))))->to_pretty_string() ==
          "x + y * (1 + 2)");
    //Mult within Add
    CHECK((NEW(Add)(NEW(Num)(1), NEW(Mult)(NEW(Num)(2), NEW(Num)(3))))->to_pretty_string() == "1 + 2 * 3");
}

TEST_CASE("Pretty Print Var Expressions") {
    //Substitution and Pretty Print
//    PTR(Expr) expr = (NEW(Add)(NEW(Var)("x"), NEW(Num)(5)))->subst("x", NEW(Mult)(NEW(Num)(2), NEW(Num)(3)));
//    CHECK(expr->to_pretty_string() == "2 * 3 + 5");
//    //Substitution with variable and Pretty Print
//    PTR(Expr) exprWithVar = (NEW(Add)(NEW(Var)("x"), NEW(Var)("y")))->subst("x", NEW(Mult)(NEW(Var)("z"), NEW(Num)(3)));
//    CHECK(exprWithVar->to_pretty_string() == "z * 3 + y");
    //Simple variable expression
    CHECK((NEW(Var)("a"))->to_pretty_string() == "a");
    //Variable addition
    CHECK((NEW(Add)(NEW(Var)("a"), NEW(Var)("b")))->to_pretty_string() == "a + b");
}

 TEST_CASE("Multiple Types of Operations"){
    CHECK((NEW(Add)(NEW(Mult)(NEW(Num)(3), NEW(Add)(NEW(Num)(4), NEW(Var)("x"))), NEW(Num)(2)))->to_pretty_string() == "3 * (4 + x) + 2");
    CHECK((NEW(Mult)(NEW(Add)(NEW(Num)(3), NEW(Mult)(NEW(Var)("y"), NEW(Num)(4))), NEW(Var)("x")))->to_pretty_string() == "(3 + y * 4) * x");
    CHECK((NEW(Add)(NEW(Mult)(NEW(Add)(NEW(Var)("a"), NEW(Num)(2)), NEW(Var)("b")), NEW(Num)(5)))->to_pretty_string() == "(a + 2) * b + 5");
    //Substitution
//    PTR(Expr) substExpr = (NEW(Mult)(NEW(Add)(NEW(Var)("x"), NEW(Num)(1)), NEW(Add)(NEW(Num)(2), NEW(Var)("y"))))->subst("x", NEW(Num)(3));
//    CHECK(substExpr->to_pretty_string() == "(3 + 1) * (2 + y)");
    //Substitution for a super nested expression
    PTR(Expr) deepNestedExpr = (NEW(Add)(NEW(Mult)(NEW(Add)(NEW(Var)("x"), NEW(Num)(4)), NEW(Var)("z")), NEW(Mult)(NEW(Var)("y"), NEW(Num)(3))));
//    CHECK(deepNestedExpr->subst("y", NEW(Add)(NEW(Num)(1), NEW(Var)("x")))->to_pretty_string() == "(x + 4) * z + (1 + x) * 3");
}

//************LET CLASS**************//

//TEST_CASE("Let hasVariable()") {
//    SECTION("rhs contains a variable") {
//        Let expr("x", NEW(Var)("y"), NEW(Num)(10));
//        CHECK(expr.has_variable() == true);
//    }
//
//    SECTION("body expression contains a variable") {
//        Let expr("x", NEW(Num)(5), NEW(Var)("y"));
//        CHECK(expr.has_variable() == true);
//    }
//
//    SECTION("Both rhs and body expression contain variables") {
//        Let expr("x", NEW(Var)("y"), NEW(Add)(NEW(Var)("y"), NEW(Num)(3)));
//        CHECK(expr.has_variable() == true);
//    }
//
//    SECTION("Neither rhs nor body expression contains variables") {
//        Let expr("x", NEW(Num)(5), NEW(Num)(10));
//        CHECK(expr.has_variable() == false);
//    }
//}

TEST_CASE("Let equals()") {
    SECTION("Equal Let expressions") {
        PTR(Let) expr1 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        PTR(Let) expr2 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        CHECK(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to lhs") {
        PTR(Let) expr1 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        PTR(Let) expr2 = NEW(Let)("y", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to rhs") {
        PTR(Let) expr1 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        PTR(Let) expr2 = NEW(Let)("x", NEW(Num)(4), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to bodyExpr") {
        PTR(Let) expr1 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        PTR(Let) expr2 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(4)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Comparing Let expression with non-Let expression") {
        PTR(Let) expr1 = NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        PTR(Expr) expr2 = NEW(Num)(5); // Using base class pointer for polymorphism
        CHECK_FALSE(expr1->equals(expr2));
    }
}
/**Subst Test: Removed**/
//TEST_CASE("Let Subst") {
//    //Tests that substituting 'x' with a new number in a Let expression where 'x' is both the bound variable and in the body doesn't affect the body due to shadowing rules.
//    CHECK((NEW(Let)("x", NEW(Num)(5), NEW(Var)("x")))->subst("x", NEW(Num)(10))->interp()->equals(NEW(NumVal)(5))); //No substitution in bodyExpr due to shadowing
//    //Tests that substituting 'y' (not the bound variable) in the rhs of a Let expression affects the final interpretation correctly.
//    CHECK((NEW(Let)("x", NEW(Var)("y"), NEW(Add)(NEW(Var)("x"), NEW(Num)(3))))->subst("y", NEW(Num)(5))->interp()->equals(NEW(NumVal)(8))); // Substitution in rhs
//    //Tests that substituting 'y' (not the bound variable) in both the rhs and the body of a Let expression affects the final interpretation correctly.
//    CHECK((NEW(Let)("x", NEW(Add)(NEW(Var)("y"), NEW(Num)(2)), NEW(Add)(NEW(Var)("x"), NEW(Var)("y"))))->subst("y", NEW(Num)(10))->interp()->equals(NEW(NumVal)(22))); //Substitution in rhs and bodyExpr
//    //Tests that substituting 'x' with a new number does not affect the Let expression when 'x' is the bound variable, demonstrating shadowing.
//    CHECK( (NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(5))))->subst("x", NEW(Num)(4))
//                   ->equals( NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(5)))));
//    //Tests that substituting 'y' (not present in the Let expression) does not change the Let expression.
//    CHECK( (NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(5))))->subst("y", NEW(Num)(4))
//                   ->equals( NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(5)))));
//    //Tests substitution of 'x' in the rhs of a Let expression when 'x' is also the bound variable, showing that rhs can still be substituted.
//    CHECK( (NEW(Let)("x", NEW(Add)(NEW(Var)("x"), NEW(Num)(8)), NEW(Add)(NEW(Var)("x"), NEW(Num)(3))))->subst("x", NEW(Num)(4))
//                   ->equals(NEW(Let)("x", NEW(Add)(NEW(Num)(4), NEW(Num)(8)), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)))) );
//    //Tests substitution of 'y' in the rhs of a Let expression when 'y' is different from the bound variable 'x'.
//    CHECK( (NEW(Let)("x", NEW(Add)(NEW(Var)("y"), NEW(Num)(8)), NEW(Add)(NEW(Var)("x"), NEW(Num)(3))))->subst("y", NEW(Num)(4))
//                   ->equals(NEW(Let)("x", NEW(Add)(NEW(Num)(4), NEW(Num)(8)), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)))) );
//    //Tests substitution of 'y' in the body of a Let expression when 'y' is different from the bound variable 'x', and 'y' is part of a nested addition.
//    CHECK( (NEW(Let)("x", NEW(Num)(6), NEW(Add)(NEW(Var)("x"), NEW(Add)(NEW(Var)("y"), NEW(Num)(7)))))->subst("y", NEW(Num)(4))
//                   ->equals(NEW(Let)("x", NEW(Num)(6), NEW(Add)(NEW(Var)("x"), NEW(Add)(NEW(Num)(4), NEW(Num)(7))))) );
//
//}

TEST_CASE("Interp") {
    //Add
    CHECK((NEW(Mult)(NEW(Num)(5), NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(1)))))->interp(Env::empty)->equals(NEW(NumVal)(30)));
    //Mult
    CHECK((NEW(Add)(NEW(Mult)(NEW(Num)(5), NEW(Let)("x", NEW(Num)(5), NEW(Var)("x"))), NEW(Num)(1)))->interp(Env::empty)->equals(NEW(NumVal)(26)));
    //Nested in right argument of multiplication expression
    CHECK ((NEW(Mult)(NEW(Mult)(NEW(Num)(2), NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(1)))),
                     NEW(Num)(3)))->interp(Env::empty)->equals(NEW(NumVal)(36)));
    //Variable is unchanged.
    CHECK_THROWS_WITH (
            (NEW(Add)(NEW(Let)("x", NEW(Num)(3), NEW(Let)("y", NEW(Num)(3), NEW(Add)(NEW(Var)("y"), NEW(Num)(2)))),
                     NEW(Var)("x")))->interp(Env::empty), "Variable has no value");
    //Lhs Add
    CHECK ((NEW(Add)(NEW(Let)("x", NEW(Num)(2), NEW(Add)(NEW(Var)("x"), NEW(Num)(9))), NEW(Num)(4)))->interp(Env::empty)->equals(NEW(NumVal)(15)));
}

TEST_CASE("Let Print()") {
    std::ostringstream os;

    SECTION("Printing simple Let expression") {
        Let expr("x", NEW(Num)(5), NEW(Var)("x"));
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in x)");
    }

    SECTION("Printing nested Let expressions") {
        Let expr("x", NEW(Num)(5), NEW(Let)("y", NEW(Num)(10), NEW(Var)("y")));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in (_let y = 10 _in y))");
    }

    SECTION("Let expression with arithmetic") {
        Let expr("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(3)));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in (x + 3))");
    }

    SECTION("Complex Let expression") {
        Let expr("x", NEW(Add)(NEW(Num)(2), NEW(Num)(3)), NEW(Mult)(NEW(Var)("x"), NEW(Num)(4)));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = (2 + 3) _in (x * 4))");
    }
}

//Ben from Nabil
TEST_CASE("Let Pretty Print") {

//Let nested as right argument of parenthesized multiplication expression
CHECK ((NEW(Mult)(NEW(Mult)(NEW(Num)(2), NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(1)))),
                 NEW(Num)(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                                                "       _in  x + 1) * 3");
//Let nested to the left in add expression which is nested to the right within a multiplication expression
CHECK((NEW(Mult)(NEW(Num)(5), NEW(Add)(NEW(Let)("x", NEW(Num)(5), NEW(Var)("x")), NEW(Num)(1))))->to_pretty_string() ==
      "5 * ((_let x = 5\n"
      "       _in  x) + 1)");
//Let in lhs of add
CHECK ((NEW(Add)(NEW(Let)("x", NEW(Num)(2), NEW(Add)(NEW(Var)("x"), NEW(Num)(9))), NEW(Num)(4)))->to_pretty_string() ==
       "(_let x = 2\n"
       "  _in  x + 9) + 4");
//Let in lhs of multiplication expression
CHECK((NEW(Mult)(NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(8))), NEW(Num)(3)))->to_pretty_string() ==
      "(_let x = 5\n"
      "  _in  x + 8) * 3");
//Let nest as right argument of un-parenthesized multiplication expression
CHECK((NEW(Add)(NEW(Mult)(NEW(Num)(4), NEW(Let)("x", NEW(Num)(5), NEW(Add)(NEW(Var)("x"), NEW(Num)(1)))),
               NEW(Num)(9)))->to_pretty_string() == "4 * (_let x = 5\n"
                                              "      _in  x + 1) + 9");
//Let nested to the left within let that is nested to the left within add
CHECK ((NEW(Add)(NEW(Let)("x", NEW(Num)(3), NEW(Let)("y", NEW(Num)(3), NEW(Add)(NEW(Var)("y"), NEW(Num)(2)))),
                NEW(Var)("x")))->to_pretty_string() == "(_let x = 3\n"
                                                      "  _in  _let y = 3\n"
                                                      "        _in  y + 2) + x");
//Let nested in lhs of Add expression nested within body of let expression
CHECK((NEW(Let)("x", NEW(Num)(5),
                   NEW(Add)(NEW(Let)("y", NEW(Num)(3), NEW(Add)(NEW(Var)("y"), NEW(Num)(2))), NEW(Var)("x"))))
              ->to_pretty_string() == "_let x = 5\n"
                                 "  _in  (_let y = 3\n"
                                 "        _in  y + 2) + x");
//Triple nested let
CHECK((NEW(Let)("x", NEW(Num)(5),
                   NEW(Add)(NEW(Let)("y", NEW(Num)(3),
                                       NEW(Add)(NEW(Var)("y"), NEW(Let)("z", NEW(Num)(6),
                                                                              NEW(Add)(NEW(Var)("a"), NEW(Num)(8))))),
                           NEW(Var)("x"))))
              ->to_pretty_string() == "_let x = 5\n"
                                 "  _in  (_let y = 3\n"
                                 "        _in  y + _let z = 6\n"
                                 "                  _in  a + 8) + x");
}

TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "Invalid Input!" );

    CHECK( parse_str("(1)")->equals(NEW(Num)(1)) );
    CHECK( parse_str("(((1)))")->equals(NEW(Num)(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "Missing close parenthesis!" );

    CHECK( parse_str("1")->equals(NEW(Num)(1)) );
    CHECK( parse_str("10")->equals(NEW(Num)(10)) );
    CHECK( parse_str("-3")->equals(NEW(Num)(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(NEW(Num)(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "Invalid Input!" );

    CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid Input!" );

    CHECK( parse_str("x")->equals(NEW(Var)("x")) );
    CHECK( parse_str("xyz")->equals(NEW(Var)("xyz")) );
    CHECK( parse_str("xYz")->equals(NEW(Var)("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "Invalid Input!" );

    CHECK( parse_str("x + y")->equals(NEW(Add)(NEW(Var)("x"), NEW(Var)("y"))) );

    CHECK( parse_str("x * y")->equals(NEW(Mult)(NEW(Var)("x"), NEW(Var)("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(NEW(Add)(NEW(Mult)(NEW(Var)("z"), NEW(Var)("x")),
                                    NEW(Var)("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(NEW(Mult)(NEW(Var)("z"),
                                     NEW(Add)(NEW(Var)("x"), NEW(Var)("y"))) ));

    //Let Tests
    CHECK(parse_str("_let x=5 _in x")->equals(NEW(Let)("x", NEW(Num)(5), NEW(Var)("x"))));
    CHECK(parse_str("_let x=5 _in (x+10)")->interp(Env::empty)->equals(NEW(NumVal)(15)));
    CHECK(parse_str("_let x=5 _in (_let y=x+2 _in y+3)")->interp(Env::empty)->equals(NEW(NumVal)(10)));
    CHECK(parse_str("_let x=3 _in x*3")->interp(Env::empty)->equals(NEW(NumVal)(9)));
    CHECK(parse_str("_let x=5 _in (_let x=3 _in x+2)")->interp(Env::empty)->equals(NEW(NumVal)(5)));
}

TEST_CASE("Testing NumVal") {

//    SECTION("to_expr") {
//        CHECK((NEW(NumVal)(1))->to_expr()->equals(NEW(Num)(1)==true);
//        CHECK((NEW(NumVal)(1))->to_expr()->equals(NEW(Num)(2)==false);
//    }

//    SECTION("equals"){
//        CHECK( (NEW(NumVal(1))->equals(NEW(NumVal(1))==true );
//        CHECK( (NEW(NumVal(1))->equals(NEW(NumVal(2))==false );
//    }

    SECTION("add_to"){
        PTR(Val) result = (NEW(NumVal)(5))->add_to(NEW(NumVal)(10));
        CHECK(result->to_string()=="15");

        PTR(Val) result2 = (NEW(NumVal)(-1))->add_to(NEW(NumVal)(-1));
        CHECK(result2->to_string()=="-2");

        PTR(Val) result3 = (NEW(NumVal)(0))->add_to(NEW(NumVal)(0));
        CHECK(result3->to_string()=="0");

        NumVal a(5);
        //TODO: Check that this is casted correctly
        PTR(Val) nonNumVal = CAST(Val)(NEW(Let)("x", NEW(Num)(1), NEW(Num)(1)));
        REQUIRE_THROWS_AS(a.add_to(nonNumVal), runtime_error);

    }

    SECTION("mult_with"){
        PTR(Val) result = (NEW(NumVal)(5))->mult_with(NEW(NumVal)(10));
        CHECK(result->to_string()=="50");

        PTR(Val) result2 = (NEW(NumVal)(-1))->mult_with(NEW(NumVal)(1));
        CHECK(result2->to_string()=="-1");

        PTR(Val) result3 = (NEW(NumVal)(0))->mult_with(NEW(NumVal)(0));
        CHECK(result3->to_string()=="0");

        NumVal a(5);
        //TODO: Check that casting a Val* is correct and doesn't need a PTR.
        PTR(Val) nonNumVal = CAST(Val)(NEW(Let)("x", NEW(Num)(1), NEW(Num)(1)));
        REQUIRE_THROWS_AS(a.mult_with(nonNumVal), runtime_error);
    }

    SECTION("print"){
        NumVal numVal(123);
        NumVal numVal2(1);
        ostringstream output;
        numVal.print(output);
        CHECK(output.str() == "123");

        ostringstream output2;
        numVal2.print(output2);
        CHECK(output2.str() == "1");
    }
}

TEST_CASE("Testing BoolVal") {

    SECTION("constructor/print") {
        BoolVal trueVal(true);
        BoolVal falseVal(false);
        ostringstream outputTrue, outputFalse;

        trueVal.print(outputTrue);
        falseVal.print(outputFalse);

        CHECK(outputTrue.str() == "1");
        CHECK(outputFalse.str() == "0");
    }

    SECTION("to_expr"){
        BoolVal boolVal(true);
        PTR(Expr) expr = boolVal.to_expr();
        ostringstream output;
        expr->print(output);
        CHECK(output.str() == "_true");

        BoolVal boolVal2(false);
        PTR(Expr) expr2 = boolVal2.to_expr();
        ostringstream output2;
        expr2->print(output2);
        CHECK(output2.str() == "_false");
    }

    SECTION("equals") {
        CHECK( (NEW(BoolVal)(true))->equals(NEW(BoolVal)(true))==true );
        CHECK( (NEW(BoolVal)(true))->equals(NEW(BoolVal)(false))==false );
    }

    SECTION("add_to") {
        PTR(BoolVal) boolVal = NEW(BoolVal)(true);
        PTR(BoolVal) anotherBoolVal = NEW(BoolVal)(false);

        REQUIRE_THROWS_AS(boolVal->add_to(anotherBoolVal), runtime_error);
    }

    SECTION("mult_with") {
        REQUIRE_THROWS_AS((NEW(BoolVal)(true))->mult_with(NEW(BoolVal)(false)), runtime_error);
    }
}

TEST_CASE("Testing BoolExpr") {

    SECTION("constructor + print"){
        BoolExpr trueExpr(true);
        BoolExpr falseExpr(false);
        ostringstream outputTrue, outputFalse;

        trueExpr.print(outputTrue);
        falseExpr.print(outputFalse);

        CHECK( outputTrue.str() == "_true" );
        CHECK( outputFalse.str() == "_false" );
    }

    SECTION("equals") {
        CHECK( (NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(true)) );
        CHECK_FALSE( (NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(false)) );
    }

    SECTION("interp") {
        BoolExpr boolExpr(true);
        PTR(Val) val = boolExpr.interp(Env::empty);
        PTR(BoolVal) boolVal = CAST(BoolVal)(val);

        REQUIRE(boolVal != nullptr); // Ensure it's a BoolVal
        ostringstream output;
        boolVal->print(output);
//        REQUIRE(output.str() == "1"); // Assuming print outputs "1" for true BoolVals
//
//        CHECK(NEW(BoolExpr)(true)->interp()->equals(NEW(BoolVal)(true)));
//        CHECK(NEW(BoolExpr)(false)->interp()==0);
    }

}

TEST_CASE("Testing IfExpr") {
    SECTION("pretty_print"){

        CHECK( (NEW(IfExpr)(NEW(EqExpr)(NEW(Var)("x"), NEW(Num)(1)), NEW(Num)(1), NEW(Num)(2)))->to_pretty_string()
               ==
               "_if x==1\n"
               "_then 1\n"
               "_else 2\n" );
    }
/**Subst Test: Removed**/
//    SECTION("IfExpr Subst"){
//        PTR(Var) varX = NEW(Var)("x");
//        PTR(Num) num1 = NEW(Num)(1);
//        PTR(Num) num2 = NEW(Num)(2);
//        PTR(Var) varY = NEW(Var)("y");
//
//        //Test substitution in the `if_` part
//        PTR(IfExpr) ifExpr1 = NEW(IfExpr)(varX, num1, num2);
//        PTR(Expr) substitutedIfExpr1 = ifExpr1->subst("x", varY);
//        ostringstream output1;
//        substitutedIfExpr1->print(output1);
//        CHECK(output1.str() == "_if y_then 1_else 2");
//
//        //Test substitution in the `then_` part
//        PTR(IfExpr) ifExpr2 = NEW(IfExpr)(num1, varX, num2);
//        PTR(Expr) substitutedIfExpr2 = ifExpr2->subst("x", varY);
//        ostringstream output2;
//        substitutedIfExpr2->print(output2);
//        CHECK(output2.str() == "_if 1_then y_else 2");
//
//        //Test substitution in the `else_` part
//        PTR(IfExpr) ifExpr3 = NEW(IfExpr)(num1, num2, varX);
//        PTR(Expr) substitutedIfExpr3 = ifExpr3->subst("x", varY);
//        ostringstream output3;
//        substitutedIfExpr3->print(output3);
//        CHECK(output3.str() == "_if 1_then 2_else y");
//    }
}

TEST_CASE("IfExpr printing") {
    auto ifExpr = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(1), NEW(Num)(2));
    ostringstream output;
    ifExpr->print(output);

    SECTION("correctly formats the expression") {
        CHECK(output.str() == "_if x_then 1_else 2");
    }
}

TEST_CASE("IfExpr pretty printing respects line breaks and indentation") {
    auto ifExpr = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(1), NEW(Num)(2));
    ostringstream output;
    streampos strmpos = 0;
    ifExpr->pretty_print_at(output,prec_none, false, strmpos);

    SECTION("includes line breaks and indentation for readability") {
        CHECK(output.str() == "_if x\n_then 1\n_else 2\n");
    }
}

//TODO: Check that this is casted correctly
TEST_CASE("IfExpr interpretation") {
    auto trueCondition = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(Num)(1), NEW(Num)(2));
    auto falseCondition = NEW(IfExpr)(NEW(BoolExpr)(false), NEW(Num)(1), NEW(Num)(2));

    SECTION("interprets `then_` branch for true condition") {
        CHECK(CAST(NumVal)(trueCondition->interp(Env::empty))->val == 1);
    }

    SECTION("interprets `else_` branch for false condition") {
        CHECK(CAST(NumVal)(falseCondition->interp(Env::empty))->val == 2);
    }
}

TEST_CASE("IfExpr equality comparison") {
    auto ifExpr1 = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(1), NEW(Num)(2));
    auto ifExpr2 = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(1), NEW(Num)(2));
    auto ifExpr3 = NEW(IfExpr)(NEW(Var)("y"), NEW(Num)(1), NEW(Num)(2)); // Different `if_`
    auto ifExpr4 = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(3), NEW(Num)(2)); // Different `then_`
    auto ifExpr5 = NEW(IfExpr)(NEW(Var)("x"), NEW(Num)(1), NEW(Num)(3)); // Different `else_`

    SECTION("identical expressions are equal") {
        CHECK(ifExpr1->equals(ifExpr2));
    }

    SECTION("different `if_` expressions are not equal") {
        CHECK_FALSE(ifExpr1->equals(ifExpr3));
    }

    SECTION("different `then_` expressions are not equal") {
        CHECK_FALSE(ifExpr1->equals(ifExpr4));
    }

    SECTION("different `else_` expressions are not equal") {
        CHECK_FALSE(ifExpr1->equals(ifExpr5));
    }
}

TEST_CASE("Testing BoolVal ") {
    SECTION("constructor/print") {
        BoolVal trueVal(true);
        BoolVal falseVal(false);
        ostringstream outputTrue, outputFalse;
        trueVal.print(outputTrue);
        falseVal.print(outputFalse);
        CHECK(outputTrue.str() == "1");
        CHECK(outputFalse.str() == "0");
    }
    SECTION("to_expr"){
        BoolVal boolVal(true);
        PTR(Expr) expr = boolVal.to_expr();
        ostringstream output;
        expr->print(output);
        CHECK(output.str() == "_true");
        BoolVal boolVal2(false);
        PTR(Expr) expr2 = boolVal2.to_expr();
        ostringstream output2;
        expr2->print(output2);
        CHECK(output2.str() == "_false");
    }
    SECTION("equals") {
        CHECK( (NEW(BoolVal)(true))->equals(NEW(BoolVal)(true))==true );
        CHECK( (NEW(BoolVal)(true))->equals(NEW(BoolVal)(false))==false );
    }
    SECTION("add_to") {
        PTR(BoolVal) boolVal = NEW(BoolVal)(true);
        PTR(BoolVal) anotherBoolVal = NEW(BoolVal)(false);

        REQUIRE_THROWS_AS(boolVal->add_to(anotherBoolVal), runtime_error);
    }
    SECTION("mult_with") {
        REQUIRE_THROWS_AS((NEW(BoolVal)(true))->mult_with(NEW(BoolVal)(false)), runtime_error);
    }
}
TEST_CASE("Testing BoolExpr") {
    SECTION("constructor, print"){
        BoolExpr trueExpr(true);
        BoolExpr falseExpr(false);
        ostringstream outputTrue, outputFalse;
        trueExpr.print(outputTrue);
        falseExpr.print(outputFalse);
        CHECK( outputTrue.str() == "_true" );
        CHECK( outputFalse.str() == "_false" );
    }
    SECTION("equals") {
        CHECK( (NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(true)) );
        CHECK_FALSE( (NEW(BoolExpr)(true))->equals(NEW(BoolExpr)(false)) );
    }
    SECTION("interp") {
        BoolExpr boolExpr(true);
        PTR(Val) val = boolExpr.interp(Env::empty);
        PTR(BoolVal) boolVal = CAST(BoolVal)(val);
        REQUIRE(boolVal != nullptr);
        ostringstream output;
        boolVal->print(output);
        REQUIRE(output.str() == "1"); // Assuming print outputs "1" for true BoolVals
    }
}

//From Sarah
TEST_CASE("Testing EqExpr 2") {
    PTR(Var) varX = NEW(Var)("x");
    PTR(Num) num1 = NEW(Num)(1);
    EqExpr eqExpr(varX, num1);
    SECTION("constructor and print") {
        ostringstream output;
        eqExpr.print(output);
        CHECK(output.str() == "x==1");
    }
    SECTION("equals") {
        PTR(Expr) condition = NEW(Var)("condition");
        PTR(Expr) num1 = NEW(Num)(1);
        PTR(Expr) num2 = NEW(Num)(2);
        PTR(Expr) varX = NEW(Var)("x");

        PTR(Expr) ifExpr = NEW(IfExpr)(condition, num1, num2);
        PTR(Expr) similarExpr = NEW(IfExpr)(condition, num1, num2);
        PTR(Expr) differentExpr = NEW(IfExpr)(NEW(EqExpr)(varX, num2), num1, num2);

        CHECK(ifExpr->equals(similarExpr) == true);
        CHECK_FALSE(ifExpr->equals(differentExpr) == true);
    }
    SECTION("interp") {
        // Assuming VarExpr::interp throws and EqExpr relies on variable resolution.
        CHECK_THROWS_AS(eqExpr.interp(Env::empty), std::runtime_error);
    }
}
TEST_CASE("Testing IfExpr 2") {
    PTR(Var) varX = NEW(Var)("x");
    PTR(Num) num1 = NEW(Num)(1);
    PTR(Num) num2 = NEW(Num)(2);
    PTR(EqExpr) condition = NEW(EqExpr)(varX, num1);
    IfExpr ifExpr(condition, num1, num2);
    SECTION("constructor and print") {
        ostringstream output;
        ifExpr.print(output);
        CHECK(output.str() == "_if x==1_then 1_else 2");
    }SECTION("pretty_print") {
        ostringstream output;
        std::string s = ifExpr.to_pretty_string();
        std::string expected = "_if x==1\n_then 1\n_else 2\n";
        CHECK(s == expected);
    }SECTION("equals") {
        PTR(Expr) condition = NEW(Var)("condition");
        PTR(Expr) num1 = NEW(Num)(1);
        PTR(Expr) num2 = NEW(Num)(2);
        PTR(Expr) varX = NEW(Var)("x");

        PTR(Expr) ifExpr = NEW(IfExpr)(condition, num1, num2);
        PTR(Expr) similarExpr = NEW(IfExpr)(condition, num1, num2);
        PTR(Expr) differentExpr = NEW(IfExpr)(NEW(EqExpr)(varX, num2), num1, num2);

        CHECK(ifExpr->equals(similarExpr) == true);
        CHECK_FALSE(ifExpr->equals(differentExpr) == true);
    }SECTION("interp") {
        // Assuming VarExpr::interp throws and IfExpr relies on condition evaluation.
        CHECK_THROWS_AS(ifExpr.interp(Env::empty), std::runtime_error);
    }SECTION("pretty_print") {
        CHECK((NEW(IfExpr)(NEW(EqExpr)(NEW(Var)("x"), NEW(Num)(1)), NEW(Num)(1), NEW(Num)(2)))->to_pretty_string()
              ==
              "_if x==1\n"
              "_then 1\n"
              "_else 2\n");
    }
}

TEST_CASE("Parse if"){
    CHECK( parse_str("_if 1==1 _then 1 _else 2") ->interp(Env::empty)->equals(NEW(NumVal)(1)));
}

TEST_CASE("Parsing BoolExpr") {
CHECK(parse_str(("_true"))->equals(NEW(BoolExpr)(true)));
CHECK(parse_str(("_false"))->equals(NEW(BoolExpr)(false)));
}

TEST_CASE("Parsing IfExpr") {
    CHECK(parse_str(("_if _true _then 4 _else 5"))->equals(
            NEW(IfExpr)(NEW(BoolExpr)(true), NEW(Num)(4), NEW(Num)(5))));
    CHECK(parse_str(("_if _false _then 4 _else 5"))->equals(
            NEW(IfExpr)(NEW(BoolExpr)(false), NEW(Num)(4), NEW(Num)(5))));
}

TEST_CASE("Parsing EqExpr") {
CHECK( parse_str("1 == 2")->interp(Env::empty)->equals(NEW(BoolVal)(false)) );
CHECK( parse_str("2 == 2")->interp(Env::empty)->equals(NEW(BoolVal)(true)) );
CHECK((parse_str("1 + 2 == 3 + 0"))->interp(Env::empty)->equals(NEW(BoolVal)(true)));
CHECK((((parse_str("_if 1 == 2 _then 3 _else 4"))->interp(Env::empty))->to_string()) == "4");
}

TEST_CASE("If Expr Interp") {
CHECK( parse_str("_if 1==1 _then 1 _else 2")->interp(Env::empty)->equals(NEW(NumVal)(1)));
CHECK( parse_str("_if 10==12 _then 7 _else 5")->interp(Env::empty)->equals(NEW(NumVal)(5)));
CHECK( parse_str("_if 0==0 _then 14 _else 7")->interp(Env::empty)->equals(NEW(NumVal)(14)));
CHECK( parse_str("_if -4==-5 _then 6 _else 8")->interp(Env::empty)->equals(NEW(NumVal)(8)));
}

TEST_CASE("FunExpr") {

    SECTION("Parsing FunExpr") {
        CHECK((parse_str("_let f = _fun (x) x+1"
                         "_in f(10)"))->interp(Env::empty)->to_string() == "11");
    }

    SECTION("Parsing FunExpr") {
        CHECK((parse_str("_let f = _fun (x) x+1"
                         " _in f(10)"))->interp(Env::empty)->to_string() == "11");
        CHECK((parse_str("_let f = _fun (x) x*x"
                         "_in f(2)"))->interp(Env::empty)->to_string() == "4");
        CHECK((parse_str("_let y = 8"
                         "_in _let f = _fun (x) x*y"
                         "_in f(2)"))->interp(Env::empty)->to_string() == "16");
        CHECK((parse_str("_let x = 8"
                         "_in _let f = _fun (x) x*x"
                         "_in f(2)"))->interp(Env::empty)->to_string() == "4");
        CHECK((parse_str("_let factrl = _fun (factrl)"
                         "_fun (x)"
                         "_if x ==1"
                         "_then 1"
                         "_else x * factrl(factrl)(x + -1)"
                         "_in factrl(factrl)(10)"))->interp(Env::empty)->to_string() == "3628800");
    }SECTION("Parsing CallExpr") {
        CHECK((parse_str("(_fun (x) x+1 (10))"))->interp(Env::empty)->to_string() == "11");
        CHECK((parse_str("(_fun (x) x+x (1))"))->interp(Env::empty)->to_string() == "2");
    }
}