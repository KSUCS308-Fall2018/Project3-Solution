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

LinkedList * lex(char *);
int parse(AST *, LinkedList *);
int evaluate(AST *);
int execute(char *);

int core_main(int argc, const char * argv[]);

#endif /* core_h */
