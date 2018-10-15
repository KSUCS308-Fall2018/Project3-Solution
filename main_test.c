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
#include "token.h"
#include "ast.h"

static char * test_evaluate() {
    mu_begin_case("evaluate", 5);
    {
        int result = mu_call_func(evaluate, NULL);
        mu_assert_i("evaluate(NULL) should return 0", 0, result);
    }

    {
        AST tree;
        AST left;
        AST right;

        tree.value = make_add_token();
        tree.left = &left;
        tree.right = &right;

        left.value = make_integer_token(5);
        left.left = NULL;
        left.right = NULL;

        right.value = make_integer_token(7);
        right.left = NULL;
        right.right = NULL;

        int result = mu_call_func(evaluate, &tree);
        mu_assert_i("+ 5 7 should be 12", 12, result);
    }

    {
        AST tree;
        AST left;
        AST right;
        AST left_left;
        AST left_right;

        tree.value = make_multiply_token();
        tree.left = &left;
        tree.right = &right;

        left.value = make_subtract_token();
        left.left = &left_left;
        left.right = &left_right;

        right.value = make_integer_token(15);
        right.left = NULL;
        right.right = NULL;

        left_left.value = make_integer_token(4);
        left_left.left = NULL;
        left_left.right = NULL;

        left_right.value = make_integer_token(2);
        left_right.left = NULL;
        left_right.right = NULL;

        int result = mu_call_func(evaluate, &tree);
        mu_assert_i("* - 4 2 15 should be 30", 30, result);
    }

    {
        AST tree;
        AST left;
        AST right;
        AST right_left;
        AST right_right;

        tree.value = make_multiply_token();
        tree.left = &left;
        tree.right = &right;

        left.value = make_integer_token(3);
        left.left = NULL;
        left.right = NULL;

        right.value = make_subtract_token();
        right.left = &right_left;
        right.right = &right_right;

        right_left.value = make_integer_token(1);
        right_left.left = NULL;
        right_left.right = NULL;

        right_right.value = make_integer_token(2);
        right_right.left = NULL;
        right_right.right = NULL;

        int result = mu_call_func(evaluate, &tree);
        mu_assert_i("* 3 - 1 2 should be -3", -3, result);
    }

    {
        AST tree;
        AST left;
        AST right;
        AST left_left;
        AST left_right;
        AST left_left_left;
        AST left_left_right;
        AST left_left_left_left;
        AST left_left_left_right;

        tree.value = make_add_token();
        tree.left = &left;
        tree.right = &right;

        left.value = make_add_token();
        left.left = &left_left;
        left.right = &left_right;

        right.value = make_integer_token(1);
        right.left = NULL;
        right.right = NULL;

        left_left.value = make_add_token();
        left_left.left = &left_left_left;
        left_left.right = &left_left_right;

        left_right.value = make_integer_token(1);
        left_right.left = NULL;
        left_right.right = NULL;

        left_left_left.value = make_add_token();
        left_left_left.left = &left_left_left_left;
        left_left_left.right = &left_left_left_right;

        left_left_right.value = make_integer_token(1);
        left_left_right.left = NULL;
        left_left_right.right = NULL;

        left_left_left_left.value = make_integer_token(1);
        left_left_left_left.left = NULL;
        left_left_left_left.right = NULL;

        left_left_left_right.value = make_integer_token(1);
        left_left_left_right.left = NULL;
        left_left_left_right.right = NULL;

        int result = mu_call_func(evaluate, &tree);
        mu_assert_i("+ + + + 1 1 1 1 1 should be 5", 5, result);
    }

    mu_end_case("evaluate");
    return 0;
}

static char * test_tokenize() {
    mu_begin_case("tokenize", 35);

    {
        Token * t = mu_call_func(tokenize, "1234", NULL);
        mu_assert_null("tokenize(\"1234\", NULL) should return NULL", t);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, NULL, &character_count);
        mu_assert_null("tokenize(NULL, &character_count) should return NULL", t);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "+", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert add token returned", ADD, t->type);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "*", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert multiply token returned", MULTIPLY, t->type);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "-", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert subtract token returned", SUBTRACT, t->type);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "         \n\n\t \t +", &character_count);
        
        mu_assert_i("Assert 16 characters read", 16, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert subtract token returned", ADD, t->type);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "1", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert integer token returned", INTEGER, t->type);
        mu_assert_i("Assert integer value correctly parsed", 1, t->value);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, " 1731", &character_count);
        
        mu_assert_i("Assert 5 characters read", 5, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert integer token returned", INTEGER, t->type);
        mu_assert_i("Assert integer value correctly parsed", 1731, t->value);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, " - 12 99", &character_count);
        
        mu_assert_i("Assert 2 characters read", 2, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert subtract token returned", SUBTRACT, t->type);
    }

    {
        int character_count = 0;
        Token * t = mu_call_func(tokenize, "12 99", &character_count);
        
        mu_assert_i("Assert 2 characters read", 2, character_count);
        mu_assert_not_null("Assert token has value", t);
        mu_assert_i("Assert integer token returned", INTEGER, t->type);
        mu_assert_i("Assert integer value correctly parsed", 12, t->value);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "abc", &character_count);
        
        mu_assert_i("Assert 0 characters read", 0, character_count);
        mu_assert_null("Assert token is null for unexpected characters", t);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "&#", &character_count);
        
        mu_assert_i("Assert 0 characters read", 0, character_count);
        mu_assert_null("Assert token is null for unexpected characters", t);
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "  ", &character_count);
        
        mu_assert_i("Assert 0 characters read", 0, character_count);
        mu_assert_null("Assert token is null for unexpected characters", t);
    }

    mu_end_case("tokenize");
    return 0;
}

static char * all_tests() {
    test_evaluate();
    test_tokenize();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    return 0;
}
#endif

