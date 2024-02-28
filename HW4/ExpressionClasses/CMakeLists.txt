cmake_minimum_required(VERSION 3.27)
project(ExpressionClasses)

set(CMAKE_CXX_STANDARD 17)

add_executable(ExpressionClasses main.cpp
        Expr.cpp
        Expr.h
        catch.h
        ExprTests.cpp
        ExprTests.h
        parse.cpp
        parse.hpp
        test_msdscript.cpp
        test_msdscript.h
)
