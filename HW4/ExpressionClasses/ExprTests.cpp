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
    CHECK((new Add(new Add(new Num(10), new Num(15)), new Add(new Num(20), new Num(20))))->interp() == 65);
}

TEST_CASE("Add Interp") {
    CHECK((new Add(new Num(3), new Num(2)))->interp() == 5);
    CHECK((new Add(new Num(5), new Num(-4)))->interp() == 1);
    CHECK((new Add(new Num(-3), new Num(3)))->interp() == 0);
    CHECK((new Add(new Num(-3), new Num(-3)))->interp() == -6);
    CHECK((new Add(new Num(0), new Num(10)))->interp() == 10);
}

TEST_CASE("Add Has Variable") {
    CHECK_FALSE((new Add(new Num(5), new Num(4)))->has_variable());
    CHECK_FALSE((new Add(new Num(0), new Num(-4)))->has_variable());
    CHECK((new Add(new Var("x"), new Num(4)))->has_variable());
    CHECK((new Add(new Num(4), new Var("y")))->has_variable());
    CHECK((new Add(new Var("x"), new Var("y")))->has_variable());
}

TEST_CASE("Add Subst") {
    CHECK((new Add(new Var("x"), new Num(3)))->subst("x", new Num(5))->interp() == 8);
    CHECK((new Add(new Num(3), new Var("x")))->subst("x", new Num(2))->interp() == 5);
    CHECK((new Add(new Num(-1), new Var("x")))->subst("x", new Num(2))->interp() == 1);
    CHECK((new Add(new Var("x"), new Var("x")))->subst("x", new Num(3))->interp() == 6);
    CHECK((new Add(new Var("y"), new Var("z")))->subst("y", new Num(3))->subst("z", new Num(2))->interp() == 5);
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
    CHECK((new Num(3))->interp() == 3);
    CHECK((new Num(5))->interp() == 5);
    CHECK((new Num(-18))->interp() == -18);
    CHECK((new Num(-3))->interp() == -3);
    CHECK((new Num(0))->interp() == 0);
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
    CHECK((new Mult(new Num(3), new Num(2)))->interp() == 6);
    CHECK((new Mult(new Num(5), new Num(4)))->interp() == 20);
    CHECK((new Mult(new Num(-3), new Num(6)))->interp() == -18);
    CHECK((new Mult(new Num(-3), new Num(-3)))->interp() == 9);
    CHECK((new Mult(new Num(0), new Num(10)))->interp() == 0);
}

TEST_CASE("Mult Has Variable") {
    CHECK_FALSE((new Mult(new Num(5), new Num(4)))->has_variable());
    CHECK_FALSE((new Mult(new Num(0), new Num(-4)))->has_variable());
    CHECK((new Mult(new Var("x"), new Num(4)))->has_variable());
    CHECK((new Mult(new Num(4), new Var("y")))->has_variable());
    CHECK((new Mult(new Var("x"), new Var("y")))->has_variable());
}

TEST_CASE("Mult Subst") {
    CHECK((new Mult(new Var("x"), new Num(3)))->subst("x", new Num(5))->interp() == 15);
    CHECK((new Mult(new Num(3), new Var("x")))->subst("x", new Num(2))->interp() == 6);
    CHECK((new Mult(new Num(-1), new Var("x")))->subst("x", new Num(2))->interp() == -2);
    CHECK((new Mult(new Var("x"), new Var("x")))->subst("x", new Num(3))->interp() == 9);
    CHECK((new Mult(new Var("y"), new Var("z")))->subst("y", new Num(3))->subst("z", new Num(2))->interp() == 6);
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
    CHECK((new Let("x", new Num(5), new Var("x")))->subst("x", new Num(10))->interp() == 5); //No substitution in bodyExpr due to shadowing
    //Tests that substituting 'y' (not the bound variable) in the rhs of a Let expression affects the final interpretation correctly.
    CHECK((new Let("x", new Var("y"), new Add(new Var("x"), new Num(3))))->subst("y", new Num(5))->interp() == 8); // Substitution in rhs
    //Tests that substituting 'y' (not the bound variable) in both the rhs and the body of a Let expression affects the final interpretation correctly.
    CHECK((new Let("x", new Add(new Var("y"), new Num(2)), new Add(new Var("x"), new Var("y"))))->subst("y", new Num(10))->interp() == 22); //Substitution in rhs and bodyExpr
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
    CHECK((new Mult(new Num(5), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))))->interp() == 30);
    //Mult
    CHECK((new Add(new Mult(new Num(5), new Let("x", new Num(5), new Var("x"))), new Num(1)))->interp() == 26);
    //Nested in right argument of multiplication expression
    CHECK ((new Mult(new Mult(new Num(2), new Let("x", new Num(5), new Add(new Var("x"), new Num(1)))),
                     new Num(3)))->interp() == 36);
    //Variable is unchanged.
    CHECK_THROWS_WITH (
            (new Add(new Let("x", new Num(3), new Let("y", new Num(3), new Add(new Var("y"), new Num(2)))),
                     new Var("x")))->interp(), "Variable has no value");
    //Lhs Add
    CHECK ((new Add(new Let("x", new Num(2), new Add(new Var("x"), new Num(9))), new Num(4)))->interp() == 15);
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
    CHECK(parse_str("_let x=5 _in (x+10)")->interp() == 15);
    CHECK(parse_str("_let x=5 _in (_let y=x+2 _in y+3)")->interp() == 10);
    CHECK(parse_str("_let x=3 _in x*3")->interp() == 9);
    CHECK(parse_str("_let x=5 _in (_let x=3 _in x+2)")->interp() == 5);
}







