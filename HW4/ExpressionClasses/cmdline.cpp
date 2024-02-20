//
// Created by Lindsay Haslam on 1/11/24.
//
//#define CATCH_CONFIG_RUNNER

#include "cmdline.h"


using namespace std;

run_mode_t use_arguments(int argc, char **argv) {
    //Set the testTextSeen to false
    bool testTextSeen = false;
    run_mode_t mode = do_nothing;

    //Loop through
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[1], "--help") == 0) {
            std::cout << "--Test: Tests the code.\n";
            std::cout << "--Help: Check your options.\n";
            std::cout << "--Print: Print.\n";
            std::cout << "--Prettyprint: Runs pretty_print_at().\n";
            exit(0);
        }
        else if (strcmp(argv[1], "--test") == 0) {
            if (!testTextSeen) {
               mode = do_tests;
//                return do_tests;
                testTextSeen = true;
            }
        }
        else if (strcmp(argv[1], "--interp") == 0) {
            return do_interp;
        }
        else if (strcmp(argv[1], "--print") == 0) {
            return do_print;
        }
        else if (strcmp(argv[1], "--prettyprint") == 0) {
            return do_pretty_print;
        }
        else {
            //For anything else that is entered in
            std::cout << "Unknown argument!";
            exit(1);
        }
    }
    return mode;
}