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


//**********VAR TESTS********//
TEST_CASE("Expr Var") {
    //Test with same name
    CHECK((new Var("x"))->equals(new Var("x")) == true );
    //Test with different name
    CHECK((new Var("x"))->equals(new Var("y")) == false);
    //Test comparing Var with a Num
    CHECK((new Var("z"))->equals(new Num(1)) == false);
    //Testing interp
    CHECK_THROWS_WITH((new Var("x"))->interp(), "Variable has no value");
}

TEST_CASE("Var Interp Throws") {
    CHECK_THROWS_AS((new Var("x"))->interp(), std::runtime_error);
    CHECK_THROWS_WITH((new Var("x"))->interp(), "Variable has no value");
}

TEST_CASE("Var Has Variable") {
    CHECK((new Var("x"))->has_variable());
    CHECK((new Var("anything"))->has_variable());
    //Even if the name is numeric, it's still a variable
    CHECK((new Var("123"))->has_variable());
}

TEST_CASE("Var Subst") {
    //Substitution matches the variable name
    CHECK((new Var("x"))->subst("x", new Num(5))->equals(new Num(5)));
    //Substitution does not match the variable name, no substitution occurs
    Expr *noSubstExpr = (new Var("x"))->subst("y", new Num(5));
    CHECK(noSubstExpr->equals(new Var("x")));
    //Substitution with another variable
    CHECK((new Var("x"))->subst("x", new Var("y"))->equals(new Var("y")));
    // Substitution with a complex expression
    CHECK((new Var("x"))->subst("x", new Add(new Num(1), new Num(2)))->equals(new Add(new Num(1), new Num(2))));
    // No substitution when variable names do not match
    Expr *noMatchSubst = (new Var("x"))->subst("z", new Num(10));
    CHECK(noMatchSubst->equals(new Var("x")));
}


//**********ADD TESTS********//
TEST_CASE("Expr Add") {
    //Same operands
    CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(2), new Num(3))) == true);
    //Different operands
    CHECK((new Add(new Num(2), new Num(3)))->equals(new Add(new Num(3), new Num(2))) == false);
    //Test comparing Add with a Var
    CHECK((new Add(new Num(1), new Num(2)))->equals(new Var("x")) == false);
    //Test with both operands being negative
    CHECK((new Add(new Num(-2), new Num(-3)))->equals(new Add(new Num(-2), new Num(-3))) == true);
    //Test with one operand being negative
    CHECK((new Add(new Num(2), new Num(-3)))->equals(new Add(new Num(2), new Num(-3))) == true);
    //Test from HW3
    CHECK( (new Add(new Add(new Num(100), new Num(100)),new Add(new Num(200),new Num(200))))
                   ->interp()->equals(new NumVal(600)));
}

TEST_CASE("Add Interp") {
    CHECK((new Add(new Num(3), new Num(2)))->interp()->equals(new NumVal(5)));
    CHECK((new Add(new Num(5), new Num(-4)))->interp()->equals(new NumVal(1)));
    CHECK((new Add(new Num(-3), new Num(3)))->interp()->equals(new NumVal(0)));
    CHECK((new Add(new Num(-3), new Num(-3)))->interp()->equals(new NumVal(-6)));
    CHECK((new Add(new Num(0), new Num(10)))->interp()->equals(new NumVal(10)));
}

TEST_CASE("Add Has Variable") {
    CHECK_FALSE((new Add(new Num(5), new Num(4)))->has_variable());
    CHECK_FALSE((new Add(new Num(0), new Num(-4)))->has_variable());
    CHECK((new Add(new Var("x"), new Num(4)))->has_variable());
    CHECK((new Add(new Num(4), new Var("y")))->has_variable());
    CHECK((new Add(new Var("x"), new Var("y")))->has_variable());
}

TEST_CASE("Add Subst") {
    CHECK((new Add(new Var("x"), new Num(3)))->subst("x", new Num(5))->interp()->equals(new NumVal(8)));
    CHECK((new Add(new Num(3), new Var("x")))->subst("x", new Num(2))->interp()->equals(new NumVal(5)));
    CHECK((new Add(new Num(-1), new Var("x")))->subst("x", new Num(2))->interp()->equals(new NumVal( 1)));
    CHECK((new Add(new Var("x"), new Var("x")))->subst("x", new Num(3))->interp()->equals(new NumVal(6)));
    CHECK((new Add(new Var("y"), new Var("z")))->subst("y", new Num(3))->subst("z", new Num(2))->interp()->equals(new NumVal(5)));
}


//**********NUM TESTS********//
TEST_CASE("Expr Num") {
    //Check that different expressions are unequal
    CHECK((new Num(1))->equals(new Var("x")) == false);
    //Check with nullpointer
    CHECK((new Num(7))->equals(nullptr) == false);
    //Check itself
    Expr *sameNum = new Num(8);
    CHECK(sameNum->equals(sameNum) == true);
    //Check two Num objects with different negative numbers
    CHECK((new Num(-3))->equals(new Num(-4)) == false);
    //Check a Num object with a negative number against a positive number
    CHECK((new Num(-2))->equals(new Num(2)) == false);
}

TEST_CASE("Num Interp") {
    CHECK((new Num(3))->interp()->equals(new NumVal(3)));
    CHECK((new Num(5))->interp()->equals(new NumVal(5)));
    CHECK((new Num(-18))->interp()->equals(new NumVal(-18)));
    CHECK((new Num(-3))->interp()->equals(new NumVal(-3)));
    CHECK((new Num(0))->interp()->equals(new NumVal(0)));
}

TEST_CASE("Num Has Variable") {
    CHECK_FALSE((new Num(5))->has_variable());
    CHECK_FALSE((new Num(0))->has_variable());
    CHECK_FALSE((new Num(-20))->has_variable());
    CHECK_FALSE((new Num(4))->has_variable());
    CHECK_FALSE((new Num(1000))->has_variable());
}

//**********MULT TESTS********//
TEST_CASE("Expr Mult") {
    //Identical multiplication expressions
    CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(2), new Num(3))) == true);
    //Different multiplication expressions
    CHECK((new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(3), new Num(2))) == false);
    //Test equality with more complex nested expressions
    CHECK((new Mult(new Add(new Num(1), new Num(2)), new Num(3)))->equals(
            new Mult(new Add(new Num(1), new Num(2)), new Num(3))) == true);
    //Test with different operands (one negative)
    CHECK((new Mult(new Num(-8), new Num(9)))->equals(new Mult(new Num(9), new Num(-8))) == false);
    //Test with a negative number in a nested expression
    CHECK((new Mult(new Add(new Num(-1), new Num(2)), new Num(3)))->equals(
            new Mult(new Add(new Num(-1), new Num(2)), new Num(3))) == true);

}

TEST_CASE("Mult Interp") {
    CHECK((new Mult(new Num(3), new Num(2)))->interp()->equals(new NumVal(6)));
    CHECK((new Mult(new Num(5), new Num(4)))->interp()->equals(new NumVal(20)));
    CHECK((new Mult(new Num(-3), new Num(6)))->interp()->equals(new NumVal(-18)));
    CHECK((new Mult(new Num(-3), new Num(-3)))->interp()->equals(new NumVal(9)));
    CHECK((new Mult(new Num(0), new Num(10)))->interp()->equals(new NumVal(0)));
}

TEST_CASE("Mult Has Variable") {
    CHECK_FALSE((new Mult(new Num(5), new Num(4)))->has_variable());
    CHECK_FALSE((new Mult(new Num(0), new Num(-4)))->has_variable());
    CHECK((new Mult(new Var("x"), new Num(4)))->has_variable());
    CHECK((new Mult(new Num(4), new Var("y")))->has_variable());
    CHECK((new Mult(new Var("x"), new Var("y")))->has_variable());
}

TEST_CASE("Mult Subst") {
    CHECK((new Mult(new Var("x"), new Num(3)))->subst("x", new Num(5))->interp()->equals(new NumVal(15)));
    CHECK((new Mult(new Num(3), new Var("x")))->subst("x", new Num(2))->interp()->equals(new NumVal(6)));
    CHECK((new Mult(new Num(-1), new Var("x")))->subst("x", new Num(2))->interp()->equals(new NumVal(-2)));
    CHECK((new Mult(new Var("x"), new Var("x")))->subst("x", new Num(3))->interp()->equals(new NumVal(9)));
    CHECK((new Mult(new Var("y"), new Var("z")))->subst("y", new Num(3))->subst("z", new Num(2))->interp()->equals(new NumVal(6)));
}


/****PRETTY PRINT TESTS*****/
TEST_CASE("Nabil's Tests for Pretty Print") {
    CHECK ((new Mult(new Num(1), new Add(new Num(2), new Num(3))))->to_pretty_string() == "1 * (2 + 3)");
    CHECK ((new Mult(new Mult(new Num(8), new Num(1)), new Var("y")))->to_pretty_string() == "(8 * 1) * y");
    CHECK ((new Mult(new Add(new Num(3), new Num(5)), new Mult(new Num(6), new Num(1))))->to_pretty_string() ==
           "(3 + 5) * 6 * 1");
    CHECK ((new Mult(new Mult(new Num(7), new Num(7)), new Add(new Num(9), new Num(2))))->to_pretty_string() ==
           "(7 * 7) * (9 + 2)");
}

TEST_CASE("Pretty Print Mult Expressions") {
    //Mult within Mult
    CHECK((new Mult(new Mult(new Num(2), new Num(3)), new Num(4)))->to_pretty_string() == "(2 * 3) * 4");
    //Mult within Mult (negative numbers)
    CHECK((new Mult(new Mult(new Num(-1), new Num(-3)), new Num(6)))->to_pretty_string() == "(-1 * -3) * 6");
    //Add within Mult
    CHECK((new Mult(new Add(new Num(1), new Num(2)), new Num(3)))->to_pretty_string() == "(1 + 2) * 3");
    //Add within Mult (negative numbers)
    CHECK((new Mult(new Add(new Num(-4), new Num(1)), new Num(5)))->to_pretty_string() == "(-4 + 1) * 5");
    //Deeply Nested
    CHECK((new Mult(new Add(new Mult(new Num(2), new Var("x")), new Num(3)),
                    new Add(new Num(4), new Var("y"))))->to_pretty_string() == "(2 * x + 3) * (4 + y)");

}

TEST_CASE("Pretty Print Add Expressions") {
    //Add within Add
    CHECK((new Add(new Add(new Num(1), new Num(2)), new Num(3)))->to_pretty_string() == "(1 + 2) + 3");
    //Mult within Add
    CHECK((new Add(new Num(1), new Mult(new Num(2), new Num(3))))->to_pretty_string() == "1 + 2 * 3");
    //Nested expressions
    CHECK((new Add(new Mult(new Num(1), new Add(new Num(2), new Num(3))), new Num(4)))->to_pretty_string() ==
          "1 * (2 + 3) + 4");
    //Nested with Variables
    CHECK((new Add(new Var("x"), new Mult(new Var("y"), new Add(new Num(1), new Num(2)))))->to_pretty_string() ==
          "x + y * (1 + 2)");
    //Mult within Add
    CHECK((new Add(new Num(1), new Mult(new Num(2), new Num(3))))->to_pretty_string() == "1 + 2 * 3");
}

TEST_CASE("Pretty Print Var Expressions") {
    //Substitution and Pretty Print
    Expr *expr = (new Add(new Var("x"), new Num(5)))->subst("x", new Mult(new Num(2), new Num(3)));
    CHECK(expr->to_pretty_string() == "2 * 3 + 5");
    //Substitution with variable and Pretty Print
    Expr *exprWithVar = (new Add(new Var("x"), new Var("y")))->subst("x", new Mult(new Var("z"), new Num(3)));
    CHECK(exprWithVar->to_pretty_string() == "z * 3 + y");
    //Simple variable expression
    CHECK((new Var("a"))->to_pretty_string() == "a");
    //Variable addition
    CHECK((new Add(new Var("a"), new Var("b")))->to_pretty_string() == "a + b");
}

 TEST_CASE("Multiple Types of Operations"){
    CHECK((new Add(new Mult(new Num(3), new Add(new Num(4), new Var("x"))), new Num(2)))->to_pretty_string() == "3 * (4 + x) + 2");
    CHECK((new Mult(new Add(new Num(3), new Mult(new Var("y"), new Num(4))), new Var("x")))->to_pretty_string() == "(3 + y * 4) * x");
    CHECK((new Add(new Mult(new Add(new Var("a"), new Num(2)), new Var("b")), new Num(5)))->to_pretty_string() == "(a + 2) * b + 5");
    //Substitution
    Expr* substExpr = (new Mult(new Add(new Var("x"), new Num(1)), new Add(new Num(2), new Var("y"))))->subst("x", new Num(3));
    CHECK(substExpr->to_pretty_string() == "(3 + 1) * (2 + y)");
    //Substitution for a super nested expression
    Expr* deepNestedExpr = (new Add(new Mult(new Add(new Var("x"), new Num(4)), new Var("z")), new Mult(new Var("y"), new Num(3))));
    CHECK(deepNestedExpr->subst("y", new Add(new Num(1), new Var("x")))->to_pretty_string() == "(x + 4) * z + (1 + x) * 3");
}

//************LET CLASS**************//

TEST_CASE("Let hasVariable()") {
    SECTION("rhs contains a variable") {
        Let expr("x", new Var("y"), new Num(10));
        CHECK(expr.has_variable() == true);
    }

    SECTION("body expression contains a variable") {
        Let expr("x", new Num(5), new Var("y"));
        CHECK(expr.has_variable() == true);
    }

    SECTION("Both rhs and body expression contain variables") {
        Let expr("x", new Var("y"), new Add(new Var("y"), new Num(3)));
        CHECK(expr.has_variable() == true);
    }

    SECTION("Neither rhs nor body expression contains variables") {
        Let expr("x", new Num(5), new Num(10));
        CHECK(expr.has_variable() == false);
    }
}

TEST_CASE("Let equals()") {
    SECTION("Equal Let expressions") {
        Let* expr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        Let* expr2 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        CHECK(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to lhs") {
        Let* expr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        Let* expr2 = new Let("y", new Num(5), new Add(new Var("x"), new Num(3)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to rhs") {
        Let* expr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        Let* expr2 = new Let("x", new Num(4), new Add(new Var("x"), new Num(3)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Different Let expressions due to bodyExpr") {
        Let* expr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        Let* expr2 = new Let("x", new Num(5), new Add(new Var("x"), new Num(4)));
        CHECK_FALSE(expr1->equals(expr2));
    }

    SECTION("Comparing Let expression with non-Let expression") {
        Let* expr1 = new Let("x", new Num(5), new Add(new Var("x"), new Num(3)));
        Expr* expr2 = new Num(5); // Using base class pointer for polymorphism
        CHECK_FALSE(expr1->equals(expr2));
    }
}

TEST_CASE("Let Subst") {
    //Tests that substituting 'x' with a new number in a Let expression where 'x' is both the bound variable and in the body doesn't affect the body due to shadowing rules.
    CHECK((new Let("x", new Num(5), new Var("x")))->subst("x", new Num(10))->interp()->equals(new NumVal(5))); //No substitution in bodyExpr due to shadowing
    //Tests that substituting 'y' (not the bound variable) in the rhs of a Let expression affects the final interpretation correctly.
    CHECK((new Let("x", new Var("y"), new Add(new Var("x"), new Num(3))))->subst("y", new Num(5))->interp()->equals(new NumVal(8))); // Substitution in rhs
    //Tests that substituting 'y' (not the bound variable) in both the rhs and the body of a Let expression affects the final interpretation correctly.
    CHECK((new Let("x", new Add(new Var("y"), new Num(2)), new Add(new Var("x"), new Var("y"))))->subst("y", new Num(10))->interp()->equals(new NumVal(22))); //Substitution in rhs and bodyExpr
    //Tests that substituting 'x' with a new number does not affect the Let expression when 'x' is the bound variable, demonstrating shadowing.
    CHECK( (new Let("x", new Num(5), new Add(new Var("x"), new Num(5))))->subst("x", new Num(4))
                   ->equals( new Let("x", new Num(5), new Add(new Var("x"), new Num(5)))));
    //Tests that substituting 'y' (not present in the Let expression) does not change the Let expression.
    CHECK( (new Let("x", new Num(5), new Add(new Var("x"), new Num(5))))->subst("y", new Num(4))
                   ->equals( new Let("x", new Num(5), new Add(new Var("x"), new Num(5)))));
    //Tests substitution of 'x' in the rhs of a Let expression when 'x' is also the bound variable, showing that rhs can still be substituted.
    CHECK( (new Let("x", new Add(new Var("x"), new Num(8)), new Add(new Var("x"), new Num(3))))->subst("x", new Num(4))
                   ->equals(new Let("x", new Add(new Num(4), new Num(8)), new Add(new Var("x"), new Num(3)))) );
    //Tests substitution of 'y' in the rhs of a Let expression when 'y' is different from the bound variable 'x'.
    CHECK( (new Let("x", new Add(new Var("y"), new Num(8)), new Add(new Var("x"), new Num(3))))->subst("y", new Num(4))
                   ->equals(new Let("x", new Add(new Num(4), new Num(8)), new Add(new Var("x"), new Num(3)))) );
    //Tests substitution of 'y' in the body of a Let expression when 'y' is different from the bound variable 'x', and 'y' is part of a nested addition.
    CHECK( (new Let("x", new Num(6), new Add(new Var("x"), new Add(new Var("y"), new Num(7)))))->subst("y", new Num(4))
                   ->equals(new Let("x", new Num(6), new Add(new Var("x"), new Add(new Num(4), new Num(7))))) );

}

TEST_CASE("Interp") {
    //Add
    CHECK((new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))))->interp()->equals(new NumVal(30)));
    //Mult
    CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->interp()->equals(new NumVal(26)));
    //Nested in right argument of multiplication expression
    CHECK ((new Mult(new Mult(new Num(2), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))),
                     new Num(3)))->interp()->equals(new NumVal(36)));
    //Variable is unchanged.
    CHECK_THROWS_WITH (
            (new Add(new Let("x", new Num(3), new Let("y", new Num(3), new Add(new Var("y"), new Num(2)))),
                     new Var("x")))->interp(), "Variable has no value");
    //Lhs Add
    CHECK ((new Add(new Let("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->interp()->equals(new NumVal(15)));
}

TEST_CASE("Let Print()") {
    std::ostringstream os;

    SECTION("Printing simple Let expression") {
        Let expr("x", new Num(5), new Var("x"));
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in x)");
    }

    SECTION("Printing nested Let expressions") {
        Let expr("x", new Num(5), new Let("y", new Num(10), new Var("y")));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in (_let y = 10 _in y))");
    }

    SECTION("Let expression with arithmetic") {
        Let expr("x", new Num(5), new Add(new Var("x"), new Num(3)));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = 5 _in (x + 3))");
    }

    SECTION("Complex Let expression") {
        Let expr("x", new Add(new Num(2), new Num(3)), new Mult(new Var("x"), new Num(4)));
        //Clear the stream
        os.str("");
        expr.print(os);
        CHECK(os.str() == "(_let x = (2 + 3) _in (x * 4))");
    }
}

//Ben from Nabil
TEST_CASE("Let Pretty Print") {

//Let nested as right argument of parenthesized multiplication expression
CHECK ((new Mult(new Mult(new Num(2), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))),
                 new Num(3)))->to_pretty_string() == "(2 * _let x = 5\n"
                                                "       _in  x + 1) * 3");
//Let nested to the left in add expression which is nested to the right within a multiplication expression
CHECK((new Mult(new Num(5), new Add(new Let("x", new Num(5), new Var("x")), new Num(1))))->to_pretty_string() ==
      "5 * ((_let x = 5\n"
      "       _in  x) + 1)");
//Let in lhs of add
CHECK ((new Add(new Let("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->to_pretty_string() ==
       "(_let x = 2\n"
       "  _in  x + 9) + 4");
//Let in lhs of multiplication expression
CHECK((new Mult(new Let("x", new Num(5), new Add(new Var("x"), new Num(8))), new Num(3)))->to_pretty_string() ==
      "(_let x = 5\n"
      "  _in  x + 8) * 3");
//Let nest as right argument of un-parenthesized multiplication expression
CHECK((new Add(new Mult(new Num(4), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))),
               new Num(9)))->to_pretty_string() == "4 * (_let x = 5\n"
                                              "      _in  x + 1) + 9");
//Let nested to the left within let that is nested to the left within add
CHECK ((new Add(new Let("x", new Num(3), new Let("y", new Num(3), new Add(new Var("y"), new Num(2)))),
                new Var("x")))->to_pretty_string() == "(_let x = 3\n"
                                                      "  _in  _let y = 3\n"
                                                      "        _in  y + 2) + x");
//Let nested in lhs of Add expression nested within body of let expression
CHECK((new Let("x", new Num(5),
                   new Add(new Let("y", new Num(3), new Add(new Var("y"), new Num(2))), new Var("x"))))
              ->to_pretty_string() == "_let x = 5\n"
                                 "  _in  (_let y = 3\n"
                                 "        _in  y + 2) + x");
//Triple nested let
CHECK((new Let("x", new Num(5),
                   new Add(new Let("y", new Num(3),
                                       new Add(new Var("y"), new Let("z", new Num(6),
                                                                              new Add(new Var("a"), new Num(8))))),
                           new Var("x"))))
              ->to_pretty_string() == "_let x = 5\n"
                                 "  _in  (_let y = 3\n"
                                 "        _in  y + _let z = 6\n"
                                 "                  _in  a + 8) + x");
}


TEST_CASE("parse") {
    CHECK_THROWS_WITH( parse_str("()"), "Invalid Input!" );

    CHECK( parse_str("(1)")->equals(new Num(1)) );
    CHECK( parse_str("(((1)))")->equals(new Num(1)) );

    CHECK_THROWS_WITH( parse_str("(1"), "Missing close parenthesis!" );

    CHECK( parse_str("1")->equals(new Num(1)) );
    CHECK( parse_str("10")->equals(new Num(10)) );
    CHECK( parse_str("-3")->equals(new Num(-3)) );
    CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
    CHECK_THROWS_WITH( parse_str("-"), "Invalid Input!" );

    CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid Input!" );

    CHECK( parse_str("x")->equals(new Var("x")) );
    CHECK( parse_str("xyz")->equals(new Var("xyz")) );
    CHECK( parse_str("xYz")->equals(new Var("xYz")) );
    CHECK_THROWS_WITH( parse_str("x_z"), "Invalid Input!" );

    CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );

    CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );

    CHECK( parse_str("z * x + y")
                   ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                                    new Var("y"))) );

    CHECK( parse_str("z * (x + y)")
                   ->equals(new Mult(new Var("z"),
                                     new Add(new Var("x"), new Var("y"))) ));

    //Let Tests
    CHECK(parse_str("_let x=5 _in x")->equals(new Let("x", new Num(5), new Var("x"))));
    CHECK(parse_str("_let x=5 _in (x+10)")->interp()->equals(new NumVal(15)));
    CHECK(parse_str("_let x=5 _in (_let y=x+2 _in y+3)")->interp()->equals(new NumVal(10)));
    CHECK(parse_str("_let x=3 _in x*3")->interp()->equals(new NumVal(9)));
    CHECK(parse_str("_let x=5 _in (_let x=3 _in x+2)")->interp()->equals(new NumVal(5)));
}

TEST_CASE("Testing NumVal") {

    SECTION("to_expr"){
        CHECK( (new NumVal(1))->to_expr()->equals((new Num(1)))==true);
        CHECK( (new NumVal(1))->to_expr()->equals((new Num(2)))==false);
    }

    SECTION("equals"){
        CHECK( (new NumVal(1))->equals(new NumVal(1))==true );
        CHECK( (new NumVal(1))->equals(new NumVal(2))==false );
    }

    SECTION("add_to"){
        Val* result = (new NumVal(5))->add_to(new NumVal(10));
        CHECK(result->to_string()=="15");

        Val* result2 = (new NumVal(-1))->add_to(new NumVal(-1));
        CHECK(result2->to_string()=="-2");

        Val* result3 = (new NumVal(0))->add_to(new NumVal(0));
        CHECK(result3->to_string()=="0");

        NumVal a(5);
        Val* nonNumVal = reinterpret_cast<Val*>(new Let("x", new Num(1), new Num(1)));
        REQUIRE_THROWS_AS(a.add_to(nonNumVal), runtime_error);

    }

    SECTION("mult_with"){
        Val* result = (new NumVal(5))->mult_with(new NumVal(10));
        CHECK(result->to_string()=="50");

        Val* result2 = (new NumVal(-1))->mult_with(new NumVal(1));
        CHECK(result2->to_string()=="-1");

        Val* result3 = (new NumVal(0))->mult_with(new NumVal(0));
        CHECK(result3->to_string()=="0");

        NumVal a(5);
        Val* nonNumVal = reinterpret_cast<Val*>(new Let("x", new Num(1), new Num(1)));
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
        Expr* expr = boolVal.to_expr();
        ostringstream output;
        expr->print(output);
        CHECK(output.str() == "_true");

        BoolVal boolVal2(false);
        Expr* expr2 = boolVal2.to_expr();
        ostringstream output2;
        expr2->print(output2);
        CHECK(output2.str() == "_false");
    }

    SECTION("equals") {
        CHECK( (new BoolVal(true))->equals(new BoolVal(true))==true );
        CHECK( (new BoolVal(true))->equals(new BoolVal(false))==false );
    }

    SECTION("add_to") {
        BoolVal boolVal(true);
        BoolVal anotherBoolVal(false);

        REQUIRE_THROWS_AS(boolVal.add_to(&anotherBoolVal), runtime_error);
    }

    SECTION("mult_with") {
        REQUIRE_THROWS_AS((new BoolVal(true))->mult_with(new BoolVal(false)), runtime_error);
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
        CHECK( (new BoolExpr(true))->equals(new BoolExpr(true)) );
        CHECK_FALSE( (new BoolExpr(true))->equals(new BoolExpr(false)) );
    }

    SECTION("interp") {
        BoolExpr boolExpr(true);
        Val* val = boolExpr.interp();
        BoolVal* boolVal = dynamic_cast<BoolVal*>(val);

        REQUIRE(boolVal != nullptr); // Ensure it's a BoolVal
        ostringstream output;
        boolVal->print(output);
//        REQUIRE(output.str() == "1"); // Assuming print outputs "1" for true BoolVals
//
//        CHECK(new BoolExpr(true)->interp()->equals(new boolVal(true)));
//        CHECK(new BoolExpr(false)->interp()==0);
    }

}

TEST_CASE("Testing IfExpr") {
    SECTION("pretty_print"){

        CHECK( (new IfExpr(new EqExpr(new Var("x"), new Num(1)), new Num(1), new Num(2)))->to_pretty_string()
               ==
               "_if x==1\n"
               "_then 1\n"
               "_else 2\n" );
    }
    SECTION("IfExpr Subst"){
        Var* varX = new Var("x");
        Num* num1 = new Num(1);
        Num* num2 = new Num(2);
        Var* varY = new Var("y");

        //Test substitution in the `if_` part
        IfExpr* ifExpr1 = new IfExpr(varX, num1, num2);
        Expr* substitutedIfExpr1 = ifExpr1->subst("x", varY);
        ostringstream output1;
        substitutedIfExpr1->print(output1);
        CHECK(output1.str() == "_if y_then 1_else 2");

        //Test substitution in the `then_` part
        IfExpr* ifExpr2 = new IfExpr(num1, varX, num2);
        Expr* substitutedIfExpr2 = ifExpr2->subst("x", varY);
        ostringstream output2;
        substitutedIfExpr2->print(output2);
        CHECK(output2.str() == "_if 1_then y_else 2");

        //Test substitution in the `else_` part
        IfExpr* ifExpr3 = new IfExpr(num1, num2, varX);
        Expr* substitutedIfExpr3 = ifExpr3->subst("x", varY);
        ostringstream output3;
        substitutedIfExpr3->print(output3);
        CHECK(output3.str() == "_if 1_then 2_else y");

        //Cleanup dynamically allocated memory
        delete ifExpr1;
        delete substitutedIfExpr1;
        delete ifExpr2;
        delete substitutedIfExpr2;
        delete ifExpr3;
        delete substitutedIfExpr3;
    }
}

TEST_CASE("IfExpr printing") {
    auto ifExpr = new IfExpr(new Var("x"), new Num(1), new Num(2));
    ostringstream output;
    ifExpr->print(output);

    SECTION("correctly formats the expression") {
        CHECK(output.str() == "_if x_then 1_else 2");
    }
}

TEST_CASE("IfExpr pretty printing respects line breaks and indentation") {
    auto ifExpr = new IfExpr(new Var("x"), new Num(1), new Num(2));
    ostringstream output;
    streampos strmpos = 0;
    ifExpr->pretty_print_at(output,prec_none, false, strmpos);

    SECTION("includes line breaks and indentation for readability") {
        CHECK(output.str() == "_if x\n_then 1\n_else 2\n");
    }
}

TEST_CASE("IfExpr interpretation") {
    auto trueCondition = new IfExpr(new BoolExpr(true), new Num(1), new Num(2));
    auto falseCondition = new IfExpr(new BoolExpr(false), new Num(1), new Num(2));

    SECTION("interprets `then_` branch for true condition") {
        CHECK(dynamic_cast<NumVal*>(trueCondition->interp())->val == 1);
    }

    SECTION("interprets `else_` branch for false condition") {
        CHECK(dynamic_cast<NumVal*>(falseCondition->interp())->val == 2);
    }
}

TEST_CASE("IfExpr equality comparison") {
    auto ifExpr1 = new IfExpr(new Var("x"), new Num(1), new Num(2));
    auto ifExpr2 = new IfExpr(new Var("x"), new Num(1), new Num(2));
    auto ifExpr3 = new IfExpr(new Var("y"), new Num(1), new Num(2)); // Different `if_`
    auto ifExpr4 = new IfExpr(new Var("x"), new Num(3), new Num(2)); // Different `then_`
    auto ifExpr5 = new IfExpr(new Var("x"), new Num(1), new Num(3)); // Different `else_`

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
        Expr* expr = boolVal.to_expr();
        ostringstream output;
        expr->print(output);
        CHECK(output.str() == "_true");
        BoolVal boolVal2(false);
        Expr* expr2 = boolVal2.to_expr();
        ostringstream output2;
        expr2->print(output2);
        CHECK(output2.str() == "_false");
    }
    SECTION("equals") {
        CHECK( (new BoolVal(true))->equals(new BoolVal(true))==true );
        CHECK( (new BoolVal(true))->equals(new BoolVal(false))==false );
    }
    SECTION("add_to") {
        BoolVal boolVal(true);
        BoolVal anotherBoolVal(false);
        REQUIRE_THROWS_AS(boolVal.add_to(&anotherBoolVal), runtime_error);
    }
    SECTION("mult_with") {
        REQUIRE_THROWS_AS((new BoolVal(true))->mult_with(new BoolVal(false)), runtime_error);
    }
}
TEST_CASE("Testing BoolExpr ") {
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
        CHECK( (new BoolExpr(true))->equals(new BoolExpr(true)) );
        CHECK_FALSE( (new BoolExpr(true))->equals(new BoolExpr(false)) );
    }
    SECTION("interp") {
        BoolExpr boolExpr(true);
        Val* val = boolExpr.interp();
        BoolVal* boolVal = dynamic_cast<BoolVal*>(val);
        REQUIRE(boolVal != nullptr);
        ostringstream output;
        boolVal->print(output);
        REQUIRE(output.str() == "1"); // Assuming print outputs "1" for true BoolVals
    }
}

//From Sarah
TEST_CASE("Testing EqExpr 2") {
    Var* varX = new Var("x");
    Num* num1 = new Num(1);
    EqExpr eqExpr(varX, num1);
    SECTION("constructor and print") {
        ostringstream output;
        eqExpr.print(output);
        CHECK(output.str() == "x==1");
    }
    SECTION("equals") {
        EqExpr similarExpr(varX, num1);
        EqExpr differentExpr(varX, new Num(2));
        CHECK(eqExpr.equals(&similarExpr));
        CHECK_FALSE(eqExpr.equals(&differentExpr));
    }
    SECTION("interp") {
        // Assuming VarExpr::interp throws and EqExpr relies on variable resolution.
        CHECK_THROWS_AS(eqExpr.interp(), std::runtime_error);
    }
}
TEST_CASE("Testing IfExpr 2") {
    Var *varX = new Var("x");
    Num *num1 = new Num(1);
    Num *num2 = new Num(2);
    EqExpr *condition = new EqExpr(varX, num1);
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
        IfExpr similarExpr(condition, num1, num2);
        IfExpr differentExpr(new EqExpr(varX, num2), num1, num2);
        CHECK(ifExpr.equals(&similarExpr));
        CHECK_FALSE(ifExpr.equals(&differentExpr));
    }SECTION("interp") {
        // Assuming VarExpr::interp throws and IfExpr relies on condition evaluation.
        CHECK_THROWS_AS(ifExpr.interp(), std::runtime_error);
    }SECTION("pretty_print") {
        CHECK((new IfExpr(new EqExpr(new Var("x"), new Num(1)), new Num(1), new Num(2)))->to_pretty_string()
              ==
              "_if x==1\n"
              "_then 1\n"
              "_else 2\n");
    }
}

TEST_CASE("Parse if"){
    CHECK( parse_str("_if 1==1 _then 1 _else 2") ->interp()->equals(new NumVal(1)));
}

TEST_CASE("Parsing BoolExpr") {
CHECK(parse_str(("_true"))->equals(new BoolExpr(true)));
CHECK(parse_str(("_false"))->equals(new BoolExpr(false)));
}

TEST_CASE("Parsing IfExpr") {
    CHECK(parse_str(("_if _true _then 4 _else 5"))->equals(
            new IfExpr(new BoolExpr(true), new Num(4), new Num(5))));
    CHECK(parse_str(("_if _false _then 4 _else 5"))->equals(
            new IfExpr(new BoolExpr(false), new Num(4), new Num(5))));
}

TEST_CASE("Parsing EqExpr") {
CHECK( parse_str("1 == 2")->interp()->equals(new BoolVal(false)) );
CHECK( parse_str("2 == 2")->interp()->equals(new BoolVal(true)) );
CHECK((parse_str("1 + 2 == 3 + 0"))->interp()->equals(new BoolVal(true)));
CHECK((((parse_str("_if 1 == 2 _then 3 _else 4"))->interp())->to_string()) == "4");
}

TEST_CASE("If Expr Interp") {
CHECK( parse_str("_if 1==1 _then 1 _else 2")->interp()->equals(new NumVal(1)));
CHECK( parse_str("_if 10==12 _then 7 _else 5")->interp()->equals(new NumVal(5)));
CHECK( parse_str("_if 0==0 _then 14 _else 7")->interp()->equals(new NumVal(14)));
CHECK( parse_str("_if -4==-5 _then 6 _else 8")->interp()->equals(new NumVal(8)));
}









