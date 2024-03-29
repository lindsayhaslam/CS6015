//
// Created by Lindsay Haslam on 2/23/24.
//

#include <iostream>
#include "test_msdscript.h"
#include "exec.h"
#include "pointer.h"

using namespace std;

static std::string random_expr_string(int depth = 0){
    if (depth > 10){
        if (rand() % 2){
            return string(1, static_cast<char>('a' + (rand() % 26)));
        } else {
            return to_string(rand() % 100);
        }
    }
    int choice = rand() % 5;
    switch(choice){
        case 0:
            return to_string(rand() % 100);
        case 1:
            return random_expr_string(depth + 1) + " + " + random_expr_string(depth + 1);
        case 2:
            return random_expr_string(depth+1) + " * " + random_expr_string(depth + 1);
        case 3:
            return string(1, static_cast<char>('a' + (rand() % 26)));
        case 4:{
            string var = string(1, static_cast<char>('a' + (rand() % 26)));
            string value = random_expr_string(depth + 1);
            string body = random_expr_string(depth + 1);
            return "_let" + var + "=" + value + "_in" + body;
        }
        default:
            return to_string(rand() % 100);
    }
}

int main (int argc, const char **argv){

    srand(static_cast<unsigned int>(time(0)));

    if (argc == 2) {
        const char *const interp1_argv[] = {argv[1], "--interp"};
        const char *const print1_argv[] = {argv[1], "--print"};
        const char *const prettyprint1_argv[] = {argv[1], "--prettyprint"};

        for (int i = 0; i < 100; i++) {
            string in = random_expr_string(0);
            cout << "Trying: \n" << in << "\n";
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult print1_result = exec_program(2, print1_argv, in);
            ExecResult prettyprint1_result = exec_program(2, prettyprint1_argv, in);

            ExecResult interp_again = exec_program(2, interp1_argv, print1_result.out);
            if (interp_again.out != interp1_result.out) {
                cout << "Different results for printed";
            }
        }
        return 0;
    }

    else if (argc == 3){
        const char * const interp1_argv[] = { argv[1], "--interp"};
        const char * const print1_argv[] = {argv[1], "--print"};
        const char * const prettyprint1_argv[] = {argv[1], "--prettyprint"};

        const char * const interp2_argv[] = {argv[2], "--interp"};
        const char * const print2_argv[] = {argv[2], "--print"};
        const char * const prettyprint2_argv[] = {argv[2], "--prettyprint"};

        for (int i = 0; i < 100; i++){
            string in = random_expr_string(0);
            std::cout << "Trying: \n" << in << "\n";

            //Test interp!
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp2_argv, in);
            if (interp1_result.out != interp2_result.out){
                cout << "Msdscript INTERP: " << interp1_result.out;
                cout << "Tester INTERP: " << interp2_result.out << "\n";
                throw std::runtime_error("Different results - INTERP!\n");
            }

            //Test print!
            ExecResult print1_result = exec_program(2, print1_argv, in);
            ExecResult print2_result = exec_program(2, print2_argv, in);
            if (print1_result.out != print2_result.out){
                cout << "Msdscript PRINT: " << print1_result.out;
                cout << "Tester PRINT: " << print2_result.out;
                throw std::runtime_error("Different results - PRINT!");
            }

            ExecResult prettyprint1_result = exec_program(2, prettyprint1_argv, in);
            ExecResult prettyprint2_result = exec_program(2, prettyprint2_argv, in);
            if (prettyprint1_result.out != prettyprint2_result.out){
                cout << "Msdscript PRETTY PRINT: " << prettyprint1_result.out;
                cout << "Tester PRETTY PRINT: " << prettyprint2_result.out;
                throw std::runtime_error("Different results - Pretty Print!");
            }
        }
        return 0;

    }

        //The input is invalid.t
    else{
        cerr << "Usage: test_msdscript <msdscript_path> or test_msdscript <msdscript_path_1> <msdscript_path_2>";
        return 1;
    }
}
