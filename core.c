//
//  core.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdlib.h>

#include "core.h"
#include "types.h"

LinkedList * lex(char * input) {
    LinkedList * head = NULL;
    
    int read = 0;
    Token * t = tokenize(input, &read);
    
    while (t != NULL) {
        input += read;
        
        LinkedList * new = malloc(sizeof(LinkedList));
        new->next = head;
        new->value = t;
        head = new;
        
        read = 0;
        t = tokenize(input, &read);
    }
    
    return reverse(head);
}

AST * parse(LinkedList * tokens, int * consumed) {
    AST * tree = NULL;
    
    if(tokens == NULL || tokens->value == NULL) {
        return NULL;
    }
    
    tree = malloc(sizeof(AST));
    
    int count = 0;
    int partial_count = 0;
    switch (tokens->value->type) {
        case ADD:
        case SUBTRACT:
        case MULTIPLY:
            tree->value = copy_token(tokens->value);
            count = 1;
            
            partial_count = 0;
            tree->left = parse(tokens->next, &partial_count);
            count += partial_count;
            
            partial_count = 0;
            tree->right = parse(advance_list(tokens, count), &partial_count);
            *consumed = count + partial_count;
            break;
        case INTEGER:
            *consumed = 1;
            tree->value = copy_token(tokens->value);
            tree->left = NULL;
            tree->right = NULL;
            break;
    }
    
    return tree;
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
    
    int consumed = 0;
    AST * tree = parse(tokens, &consumed);
    
    int result = evaluate(tree);
    
    free_tree(tree);
    free_list(tokens);
    
    return result;
}

int core_main(int argc, const char * argv[]) {
    char input[100];
    
    while (TRUE) {
        printf(":> ");
        fgets(input, 100, stdin);
        printf("   = %d\n", execute(input));
    }

    return 0;
}
