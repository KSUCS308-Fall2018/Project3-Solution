//
//  ast.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdlib.h>

#include "ast.h"

void free_tree(AST * tree) {
    if (tree == NULL) {
        return;
    }
    
    free_tree(tree->left);
    free_tree(tree->right);
    
    free(tree->value);
    free(tree);
}

