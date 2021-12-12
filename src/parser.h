#ifndef PARSER_H
#define PARSER_H

#include "logger.h"

#define ID_SIZE 2

typedef enum {
    add_item, // Add item to list
    delete_item, // Delete an item from list
    list_items, // Show the list
    finish_item // Move item to done sublist (not deleting it!)
} Operation;

typedef struct Arguments {
     Operation op;   
     char **item;
     int item_length;
     char *itemid;
} Arguments;

Arguments parse(int argc, char **argv);

#endif

