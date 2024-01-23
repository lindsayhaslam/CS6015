//
// Created by Lindsay Haslam on 1/18/24.
//

#include "ExprTests.h"

TEST_CASE("Expr Var"){
    //Test with same name
    CHECK( (new Var("x"))->equals(new Var("x")) == true );
    //Test with different name
    CHECK( (new Var("x"))->equals(new Var("y")) == false );
    //Test comparing Var with a Num
    CHECK( (new Var("z"))->equals(new Num(1)) == false );
}

TEST_CASE("Expr Add"){
    //Same operands
    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(2),new Num(3)))==true );
    //Different operands
    CHECK( (new Add(new Num(2),new Num(3)))->equals(new Add(new Num(3),new Num(2)))==false );
    //Test comparing Add with a Var
    CHECK( (new Add(new Num(1), new Num(2)))->equals(new Var("x")) == false );
    // Test with both operands being negative
    CHECK( (new Add(new Num(-2), new Num(-3)))->equals(new Add(new Num(-2), new Num(-3))) == true );
    // Test with one operand being negative
    CHECK( (new Add(new Num(2), new Num(-3)))->equals(new Add(new Num(2), new Num(-3))) == true );
}

TEST_CASE("Expr Num"){
    //Check that different expressions are unequal
    CHECK( (new Num(1))->equals(new Var("x")) == false );
    //Check with nullpointer
    CHECK( (new Num(7))->equals(nullptr) == false );
    //Check itself
    Expr* sameNum = new Num(8);
    CHECK( sameNum->equals(sameNum) == true );
    // Check two Num objects with different negative numbers
    CHECK( (new Num(-3))->equals(new Num(-4)) == false );
    // Check a Num object with a negative number against a positive number
    CHECK( (new Num(-2))->equals(new Num(2)) == false );
}

TEST_CASE("Expr Mult"){
    //Identical multiplication expressions
    CHECK( (new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(2), new Num(3))) == true );
    //Different multiplication expressions
    CHECK( (new Mult(new Num(2), new Num(3)))->equals(new Mult(new Num(3), new Num(2))) == false );
    //Test equality with more complex nested expressions
    CHECK( (new Mult(new Add(new Num(1), new Num(2)), new Num(3)))->equals(new Mult(new Add(new Num(1), new Num(2)), new Num(3))) == true );
    // Test with different operands (one negative)
    CHECK( (new Mult(new Num(-8), new Num(9)))->equals(new Mult(new Num(9), new Num(-8))) == false );
    // Test with a negative number in a nested expression
    CHECK( (new Mult(new Add(new Num(-1), new Num(2)), new Num(3)))->equals(new Mult(new Add(new Num(-1), new Num(2)), new Num(3))) == true );
}


