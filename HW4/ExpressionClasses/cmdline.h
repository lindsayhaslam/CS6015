//
// Created by Lindsay Haslam on 1/11/24.
//

#ifndef EXPRESSIONCLASSES_CMDLINE_H
#define EXPRESSIONCLASSES_CMDLINE_H

#include "catch.h"
#include <cstring>
#include <iostream>

typedef enum {
    do_tests,
    do_nothing,
    do_help,
    do_interp,
    do_print,
    do_pretty_print,
} run_mode_t;

run_mode_t use_arguments(int argc, char **argv);


#endif //HW1_CMDLINE_H
