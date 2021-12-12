#ifndef PARSER_H
#define PARSER_H

#include "logger.h"

#define ID_SIZE 2

typedef enum {
    ADD_ITEM, // Add item to list
    DELETE_ITEM, // Delete an item from list
    LIST_ITEMS, // Show the list
    FINISH_ITEM // Move item to done sublist (not deleting it!)
} Operation;

typedef struct Arguments {
     Operation op;   
     char **item;
     int item_length;
     char *itemid;
     char *listid;
} Arguments;

Arguments parse(int argc, char **argv);

#endif

