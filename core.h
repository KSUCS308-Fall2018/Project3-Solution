//
//  core.h
//  Project 3 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef core_h
#define core_h

#include <stdio.h>

#include "types.h"
#include "linked_list.h"
#include "ast.h"

LinkedList * lex(char * input);
int parse(AST * tree, LinkedList * tokens);
int evaluate(AST * tree);
int execute(char * input);

int core_main(int argc, const char * argv[]);

#endif /* core_h */
