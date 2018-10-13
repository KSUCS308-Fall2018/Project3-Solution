//
//  token.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "types.h"

bool is_digit(char c) {
    return (c <= '9' && c >= '0');
}

bool is_whitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

Token * copy_token(Token * token) {
    if (token == NULL) {
        return NULL;
    }
    
    Token * t = malloc(sizeof(Token));
    memcpy(t, token, sizeof(Token));
    
    return t;
}

Token * make_add_token() {
    Token * t = malloc(sizeof(Token));
    t->type = ADD;
    return t;
}

Token * make_subtract_token() {
    Token * t = malloc(sizeof(Token));
    t->type = SUBTRACT;
    return t;
}

Token * make_multiply_token() {
    Token * t = malloc(sizeof(Token));
    t->type = MULTIPLY;
    return t;
}

Token * make_integer_token(int value) {
    Token * t = malloc(sizeof(Token));
    t->type = INTEGER;
    t->value = value;
    return t;
}

Token * tokenize(char * str, int * characters_read) {
    if (characters_read == NULL) {
        return NULL;
    }
    
    *characters_read = 0;
    
    if (str == NULL) {
        return NULL;
    }
    
    while (is_whitespace(*str)) {
        (*characters_read)++;
        str++;
    }
    
    switch (*str) {
        case '+':
            (*characters_read)++;
            return make_add_token();
            
        case '-':
            (*characters_read)++;
            return make_subtract_token();
        case '*':
            (*characters_read)++;
            return make_multiply_token();
    }
    
    int value = 0;
    if (is_digit(*str)) {
        value = (*str) - '0';
        (*characters_read)++;
        str++;
        while (is_digit(*str)) {
            value *= 10;
            value += (*str) - '0';
            (*characters_read)++;
            str++;
        }
        
        return make_integer_token(value);
    }

    (*characters_read) = 0;
    return NULL;
}

