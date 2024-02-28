//
// Created by Lindsay Haslam on 2/23/24.
//

#include <iostream>
#include "test_msdscript.h"
#include "exec.h"

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

//Random Num (these all just generate)
//Random Var
//Random_add (random expr generator)
//***Switch case for random expr generator (see lecture), randomize logic from slide 22.
//OneCommand method from the slides (Lecture 13, slide 28 comparison against yourself).
//Slide 29 is for against another script, these are two separate methods.
//Main should test

//Generate a random expression string
//Generate a random let body
//Generate a random variable

//Call random string expression, and run the code from his slides
//This is for the comparisons, when arg == 2
//If Argc == 3, then we are doing comparisons.
//etc.
//Copy and paste for 28, add prettyprint, copy the print result and interp_again_result, and then change those to pretty print.
//Create two functions
//Comparing against yourself, is two arguments.
//Comparing against two others, there are three arguments.

//This is mostly ready for comparing against two others.//This is two commands but is taking three for comparison between two
//I need OneCommands, which is argv[1] for everything. Copy from slide 28. Change "msdscript" to argv[1]. Then add a pretty print.
//Everything in the for loop is in the slides. Add a pretty print const char.
//Copy and paste print_result and interp_again result, but swap print_result with prettyPrint_result.


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

        //catch if the input is invalid
    else{
        cerr << "Usage: test_msdscript <msdscript_path> or test_msdscript <msdscript_path_1> <msdscript_path_2>";
        return 1;
    }
}

//    //Comparing three arguments (scripts against each other)
//    const char *const interp1_argv[] = {argv[1], "--interp"};
//    //Change this to the second slide
//    const char *const interp2_argv[] = {argv[2], "--interp"};
//    //Do the same thing for print and pretty print
//
//
//    //Incorporate for pretty print
//
//    //Copy and paste the two lines (inerpt_result) and (interp_then change them to prettyPrint_results.
//    //Copy and paste the two interp_again_resultPP.
//
//    for (int i = 0; i < 100; i++){
//        string in = random_expr_string();
//        std::cout << "Trying " << in << "\n";
//
//        ExecResult interp1_result = exec_program(2, interp1_argv, in);
//        ExecResult interp2_result = exec_program(2, interp2_argv, in);
//        //Then do the same thing for print and pretty print.
//        //Copy and paste the below, but change interp_again_resultPP.
//        if (interp1_result.out != interp2_result.out){
//            throw runtime_error("Different results!");
//        }
//    }
//    return 0;
//}
