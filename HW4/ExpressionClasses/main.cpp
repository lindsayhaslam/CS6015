/**
 * \file main.cpp
 * \author Lindsay Haslam
 * \date 2/6/2024
 * \brief Main entry point for the program.
 * This file contains the main function that serves as the entry point of the program.
 */

#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "cmdline.h"
#include "Expr.h"
#include "parse.hpp"
#include "catch.h"

using namespace std;

int main(int argc, char **argv) {
    run_mode_t runType = use_arguments(argc, argv);

    switch (runType) {
        case do_help:
            cout << "--Test: Tests the code.\n";
            cout << "--Help: Check your options.\n";
            cout << "--Print: Print.\n";
            cout << "--Prettyprint: Runs pretty_print_at().\n";
            break;
        case do_tests:
            std::cout << "Before if sessions";
            if(Catch::Session().run(1, argv) != 0){
                std::cerr << "Tests failed.\n";
                exit(1);
            }
            else {
                std::cout << "Tests passed!";
                exit(0);
            }
        case do_interp: {
            PTR(Expr) e = parse(std::cin);
            std::cout << e->interp() << "\n";
            break;
        }
        case do_print: {
            PTR(Expr) e = parse(std::cin);
            std::cout << e->to_string() << "\n";
            break;
        }
        case do_pretty_print: {
            PTR(Expr) e = parse(std::cin);
            std::cout << e->to_pretty_string() << "\n";
            break;
        }
        case do_nothing:
        default:
            do_nothing;
            break;
    }

    return 0;
}
