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


Token * tokenize(char * str, int * read) {
    if (read == NULL) {
        return NULL;
    }
    
    *read = 0;
    
    if (str == NULL) {
        return NULL;
    }
    
    while (is_whitespace(*str)) {
        (*read)++;
        str++;
    }
    
    Token * t = malloc(sizeof(Token));
    
    switch (*str) {
        case '+':
            (*read)++;
            t->type = ADD;
            return t;
            
        case '-':
            (*read)++;
            t->type = SUBTRACT;
            return t;
            
        case '*':
            (*read)++;
            t->type = MULTIPLY;
            return t;
    }
    
    int value = 0;
    if (is_digit(*str)) {
        value = (*str) - '0';
        (*read)++;
        str++;
        while (is_digit(*str)) {
            value *= 10;
            value += (*str) - '0';
            (*read)++;
            str++;
        }
        
        t->type = INTEGER;
        t->value = value;
        return t;
    }
    
    free(t);
    return NULL;
}

