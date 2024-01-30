//
// Created by Lindsay Haslam on 1/11/24.
//
#include <iostream>
#include "cmdline.h"
#include <cstring>

using namespace std;

void use_arguments(int argc, char **argv) {
    //Set the testTextSeen to false
    bool testTextSeen = false;

    //Loop through
    for (int i = 1; i < argc; i++)
    if (strcmp(argv[1], "--help") == 0) {
        std::cout<<"--Test: Tests the code.\n";
        std::cout<<"--Help: Check your options.\n";
        exit(0);
    }
    else if(strcmp(argv[1], "--test") == 0){
        if(!testTextSeen){
            std::cout<< "Tests passed.\n";
            //Screen for double --test
            testTextSeen = true;
        } else{
            std::cerr<<"Error! You cannot run the test twice.";
            exit(1);
        }
    }
    else{
        //For anything else that is entered in
        std::cout<< "Unknown argument!";
        exit(1);
    }
}