#ifndef TD_H
#define TD_H
#include "parser.h"

#define LINE_SIZE 256
#define MAX_LINES 100

int add(Arguments *args);
int list(Arguments *args);
int finish(Arguments *args);
int edit(Arguments *args);

#endif
