//
//  main_test.c
//  Project 3 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "min_unit.h"
#include "core.h"

static char * test_assert() {
    mu_begin_case("assert");

    {
        mu_assert_i("Assert", 0, 0);
    }

    mu_end_case("assert");
    return 0;
}

static char * all_tests() {
    test_assert();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    return 0;
}
#endif

