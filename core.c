//
//  core.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "types.h"

LinkedList * lex(char * input) {
    LinkedList * head = NULL;
    
    int read = 0;
    Token * t = tokenize(input, &read);
    
    while (t != NULL) {
        input += read;
        
        head = append(head, t);
        
        read = 0;
        t = tokenize(input, &read);
    }
    
    return head;
}

int parse(AST * tree, LinkedList * tokens) {
    if(tree == NULL || tokens == NULL || tokens->value == NULL) {
        return 0;
    }

    int count = 0;

    switch (tokens->value->type) {
        case ADD:
        case SUBTRACT:
        case MULTIPLY:
            tree->value = copy_token(tokens->value);
            count++;
            
            tree->left = malloc(sizeof(AST));
            count += parse(tree->left, tokens->next);
            
            tree->right = malloc(sizeof(AST));
            count += parse(tree->right, advance_list(tokens, count));
            break;
        case INTEGER:
            tree->value = copy_token(tokens->value);
            tree->left = NULL;
            tree->right = NULL;
            count++;
            break;
    }
    return count;
}

int evaluate(AST * tree) {
    if (tree == NULL) {
        printf("Runtime error\n");
        return 0;
    }
    
    switch (tree->value->type) {
        case ADD:
            return evaluate(tree->left) + evaluate(tree->right);
        case SUBTRACT:
            return evaluate(tree->left) - evaluate(tree->right);
        case MULTIPLY:
            return evaluate(tree->left) * evaluate(tree->right);
        case INTEGER:
            return tree->value->value;
    }
}

int execute(char * input) {
    if (input == NULL) {
        return 0;
    }
    
    LinkedList * tokens = lex(input);
    
    AST * tree = malloc(sizeof(AST));
    parse(tree, tokens);
    
    int result = evaluate(tree);
    
    free_tree(tree);
    free_list(tokens);
    
    return result;
}

int core_main(int argc, const char * argv[]) {
    char input[100];
    
    printf(":> ");
    fgets(input, 100, stdin);
    while(strcmp(input, "q\n")) {
        printf("   = %d\n", execute(input));
        printf(":> ");
        fgets(input, 100, stdin);
    } 

    return 0;
}

// Just returns of evaluate
// lex, but not tokenize
// parse
// free_tree
// free_list
