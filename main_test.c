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
        if (t != NULL) {
            mu_assert_i("Assert add token returned", ADD, t->type);
        } else {
            mu_assert_i("(SKIPPING) Assert add token returned", ADD, SUBTRACT);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "*", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert multiply token returned", MULTIPLY, t->type);
        } else {
            mu_assert_i("(SKIPPING) Assert multiply token returned", MULTIPLY, ADD);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "-", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert subtract token returned", SUBTRACT, t->type);
        } else {
            mu_assert_i("(SKIPPING) Assert subtract token returned", SUBTRACT, ADD);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "         \n\n\t \t +", &character_count);
        
        mu_assert_i("Assert 16 characters read", 16, character_count);
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert subtract token returned", ADD, t->type);
        } else {
            mu_assert_i("(SKIPPING) Assert subtract token returned", ADD, SUBTRACT);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, "1", &character_count);
        
        mu_assert_i("Assert 1 character read", 1, character_count);
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert integer token returned", INTEGER, t->type);
            mu_assert_i("Assert integer value correctly parsed", 1, t->value);
        } else {
            mu_assert_i("(SKIPPING) Assert integer token returned", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert integer value correctly parsed", 1, 0);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, " 1731", &character_count);
        
        mu_assert_i("Assert 5 characters read", 5, character_count);
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert integer token returned", INTEGER, t->type);
            mu_assert_i("Assert integer value correctly parsed", 1731, t->value);
        } else {
            mu_assert_i("(SKIPPING) Assert integer token returned", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert integer value correctly parsed", 1731, 0);
        }
    }

    {
        int character_count;
        Token * t = mu_call_func(tokenize, " - 12 99", &character_count);
        
        mu_assert_i("Assert 2 characters read", 2, character_count);
        mu_assert_not_null("Assert token has value", t);
        if (t != NULL) {
            mu_assert_i("Assert subtract token returned", SUBTRACT, t->type);
        } else {
            mu_assert_i("(SKIPPING) Assert subtract token returned", SUBTRACT, ADD);
        }
    }

    {
        int character_count = 0;
        Token * t = mu_call_func(tokenize, "12 99", &character_count);
        
        mu_assert_i("Assert 2 characters read", 2, character_count);
        mu_assert_not_null("Assert token has value", t);

        if (t != NULL) {
            mu_assert_i("Assert integer token returned", INTEGER, t->type);
            mu_assert_i("Assert integer value correctly parsed", 12, t->value);
        } else {
            mu_assert_i("(SKIPPING) Assert integer token returned", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert integer value correctly parsed", 12, 0);
        }
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


static char * test_parse() {
    mu_begin_case("parse", 36);

    {
        AST tree;
        int consumed = mu_call_func(parse, &tree, NULL);
        mu_assert_i("parse(&tree, NULL) should return 0", 0, consumed);
    }

    {
        LinkedList l;
        int consumed = mu_call_func(parse, NULL, &l);
        mu_assert_i("parse(&tree, NULL) should return 0", 0, consumed);
    }

    {
        AST tree;
        tree.left = NULL;
        tree.right = NULL;

        LinkedList * head = append(NULL, make_add_token());
        head = append(head, make_integer_token(1));
        head = append(head, make_integer_token(2));

        int consumed = mu_call_func(parse, &tree, head);

        mu_assert_i("Assert 3 items consumed", 3, consumed);
        mu_assert_i("Assert root is ADD token", ADD, tree.value->type);

        mu_assert_not_null("Assert left node has value", tree.left);
        if (tree.left != NULL) {
            mu_assert_i("Assert left token is INTEGER token", INTEGER, tree.left->value->type);
            mu_assert_i("Assert left token has value 1", 1, tree.left->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert left token is INTEGER token", INTEGER, MULTIPLY);
            mu_assert_i("(SKIPPING) Assert left token has value 1", 1, 0);
        }

        mu_assert_not_null("Assert right node has value", tree.right);
        if (tree.right != NULL) {
            mu_assert_i("Assert right token is INTEGER token", INTEGER, tree.right->value->type);
            mu_assert_i("Assert right token has value 2", 2, tree.right->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert right token is INTEGER token", INTEGER, MULTIPLY);
            mu_assert_i("(SKIPPING) Assert right token has value 2", 2, 0);
        }
    }

    {
        AST tree;
        tree.left = NULL;
        tree.right = NULL;

        LinkedList * head = append(NULL, make_multiply_token());
        head = append(head, make_subtract_token());
        head = append(head, make_integer_token(1));
        head = append(head, make_integer_token(2));
        head = append(head, make_integer_token(3));

        int consumed = mu_call_func(parse, &tree, head);

        mu_assert_i("Assert 5 items consumed", 5, consumed);
        mu_assert_i("Assert root is MULTIPLY token", MULTIPLY, tree.value->type);

        mu_assert_not_null("Assert left node has value", tree.left);
        if (tree.left != NULL) {
            mu_assert_i("Assert left token is SUBTRACT token", SUBTRACT, tree.left->value->type);
        } else {
            mu_assert_i("(SKIPPING) Assert left token is SUBTRACT token", SUBTRACT, ADD);
        }

        mu_assert_not_null("Assert right node has value", tree.right);
        if (tree.right != NULL) {
            mu_assert_i("Assert right token is INTEGER token", INTEGER, tree.right->value->type);
            mu_assert_i("Assert right token has value 3", 3, tree.right->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert right token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert right token has value 3", 3, 0);
        }

        if (tree.left != NULL) {
            mu_assert_not_null("Assert left left node has value", tree.left->left);
        } else {
            mu_assert_not_null("(SKIPPING) Assert left left node has value", NULL);
        }

        if (tree.left != NULL && tree.left->left != NULL){
            mu_assert_i("Assert left left token is INTEGER token", INTEGER, tree.left->left->value->type);
            mu_assert_i("Assert left left token has value 1", 1, tree.left->left->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert left left token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert left left token has value 1", 1, 0);
        }

        if (tree.left != NULL) {
            mu_assert_not_null("Assert left right node has value", tree.left->right);
        } else {
            mu_assert_not_null("(SKIPPING) Assert left right node has value", NULL);
        }

        if (tree.left != NULL && tree.left->right) {
            mu_assert_i("Assert left right token is INTEGER token", INTEGER, tree.left->right->value->type);
            mu_assert_i("Assert left right token has value 2", 2, tree.left->right->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert left right token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert left right token has value 2", 2, 0);
        }
    }

    {
        AST tree;
        tree.left = NULL;
        tree.right = NULL;

        LinkedList * head = append(NULL, make_multiply_token());
        head = append(head, make_integer_token(1));
        head = append(head, make_multiply_token());
        head = append(head, make_integer_token(2));
        head = append(head, make_integer_token(3));

        int consumed = mu_call_func(parse, &tree, head);

        mu_assert_i("Assert 5 items consumed", 5, consumed);
        mu_assert_i("Assert root is MULTIPLY token", MULTIPLY, tree.value->type);

        mu_assert_not_null("Assert left node has value", tree.left);
        if (tree.left != NULL) {
            mu_assert_i("Assert left token is INTEGER token", INTEGER, tree.left->value->type);
            mu_assert_i("Assert left token has value 1", 1, tree.left->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert left token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert left token has value 1", 1, 0);
        }

        mu_assert_not_null("Assert right node has value", tree.right);
        if (tree.right != NULL) {
            mu_assert_i("Assert right token is MULTIPLY token", MULTIPLY, tree.right->value->type);
        } else {
            mu_assert_i("(SKIPPING) Assert right token is MULTIPLY token", MULTIPLY, ADD);
        }

        if (tree.right != NULL) {
            mu_assert_not_null("Assert right left node has value", tree.right->left);
        } else {
            mu_assert_not_null("(SKIPPING) Assert right left node has value", NULL);
        }

        if (tree.right != NULL && tree.right->left != NULL) {
            mu_assert_i("Assert right left token is INTEGER token", INTEGER, tree.right->left->value->type);
            mu_assert_i("Assert right left token has value 2", 2, tree.right->left->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert right left token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert right left token has value 2", 2, 0);
        }

        if (tree.right != NULL) {
            mu_assert_not_null("Assert right right node has value", tree.right->right);
        } else {
            mu_assert_not_null("(SKIPPING) Assert right right node has value", NULL);
        }

        if (tree.right != NULL && tree.right->right != NULL) {
            mu_assert_i("Assert right right token is INTEGER token", INTEGER, tree.right->right->value->type);
            mu_assert_i("Assert right right token has value 3", 3, tree.right->right->value->value);
        } else {
            mu_assert_i("(SKIPPING) Assert right right token is INTEGER token", INTEGER, ADD);
            mu_assert_i("(SKIPPING) Assert right right token has value 3", 3, 0);
        }
    }

    mu_end_case("parse");
    return 0;
}

static char * all_tests() {
    test_evaluate();
    test_tokenize();
    test_parse();
    return 0;
}

#ifdef TEST
int main(int argc, char **argv) {
    mu_run(all_tests);
    return 0;
}
#endif

