//
//  linked_list.c
//  Project 3
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#include <stdlib.h>

#include "linked_list.h"

LinkedList * reverse(LinkedList * list) {
    if (list == NULL) {
        return NULL;
    }
    
    LinkedList * previous = NULL;
    LinkedList * current = list;
    LinkedList * next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    
    return previous;
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
