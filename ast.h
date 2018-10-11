//
//  ast.h
//  Project 3 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef ast_h
#define ast_h

#include "token.h"

typedef struct AST {
    Token * value;
    struct AST * left;
    struct AST * right;
} AST;

void free_tree(AST *);

#endif /* linked_list_h */
