//
//  linked_list.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdlib.h>

#include "linked_list.h"

LinkedList * append(LinkedList * head, Token * token) {
    LinkedList * new = malloc(sizeof(LinkedList));
    new->value = token;
    new->next = NULL;
    
    if (head == NULL) {
        return new;
    }
    
    LinkedList * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new;
    
    return head;
}

LinkedList * advance_list(LinkedList * list, int steps) {
    while (list != NULL && steps > 0) {
        list = list->next;
        steps--;
    }
    
    return list;
}

void free_list(LinkedList * list) {
    while (list != NULL) {
        LinkedList * next = list->next;
        free(list->value);
        free(list);
        list = next;
    }
}
