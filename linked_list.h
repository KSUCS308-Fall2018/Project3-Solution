//
//  linked_list.h
//  Project 3 
//
//  Created by Ashley Coleman on 7/5/18.
//  Copyright © 2018 Ashley Coleman. All rights reserved.
//

#ifndef linked_list_h
#define linked_list_h

#include "token.h"

typedef struct LinkedList {
    Token * value;
    struct LinkedList * next;
} LinkedList;

LinkedList * append(LinkedList *, Token *);
LinkedList * advance_list(LinkedList * , int);
void free_list(LinkedList * list);

#endif /* linked_list_h */
