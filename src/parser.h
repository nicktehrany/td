#ifndef PARSER_H
#define PARSER_H

#include "logger.h"

#define ID_SIZE 2

typedef enum {
    ADD,
    FINISH,
    LIST,
    EDIT
} Operation;

typedef struct Arguments {
     Operation op;   
     char **item;
     int item_length;
     int num_items;
     char *itemid;
} Arguments;

Arguments parse(int argc, char **argv);

#endif

