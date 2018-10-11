//
//  token.h
//  Project 3 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef token_h
#define token_h

typedef struct Token {
    enum { MULTIPLY, ADD, SUBTRACT, INTEGER} type;
    int value;
} Token;

Token * copy_token(Token *);
Token * tokenize(char *, int *);

#endif /* token_h */
