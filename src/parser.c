#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

Arguments parse(int argc, char **argv) {
    Operation op = LIST_ITEMS; // By default if no other flag, list items
    char **item;
    int item_length = 0; // the number of char* in the **item
    char *itemid = NULL;
    char val;
    int opt;
    bool parsed = false;
    int arg_index = 0;
    char *listid = NULL;

    // Allow long options (e.g. --add instead of -a)
    static struct option long_options[] = {
        {"add", required_argument , NULL, 'a'},
        {"delete", required_argument , NULL, 'd'},
        {"list", no_argument , NULL, 'l'},
        {"finish", no_argument , NULL, 'f'},
        {"help", no_argument , NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    while((opt = getopt_long(argc, argv, "hla:f:d:", long_options, NULL)) != -1) 
    { 
        arg_index++;
        switch(opt) 
        { 
            case 'a':
                op = ADD_ITEM;
                item = malloc((argc - arg_index - 1) * sizeof(*item));

                // If we get -a flag rest is item text
                for (int i = arg_index + 1; i < argc; i++) {
                    item[item_length] = strdup(argv[i]);
                    item[item_length] = (i < argc - 1) ? strcat(item[item_length], " ") : strcat(item[item_length], "\n");
                    item_length++;
                    parsed = true;
                }
                break;
            case 'f':
                op = FINISH_ITEM;
                itemid = optarg; 
                parsed = true;
                break;
            case 'd':
                op = DELETE_ITEM;
                itemid = optarg; 
                parsed = true;
                break;
            case 'l':
                op = LIST_ITEMS;
                if(arg_index + 1 < argc) {
                    int length = strlen(argv[arg_index + 1]);
                    listid = malloc(length * sizeof(char *) + 1);
                    memcpy(listid, argv[arg_index + 1], length);
                    listid[strlen(argv[arg_index + 1])] = '\0';
                }
                parsed = true;
                break;
            case 'h':
                // TODO print help
                exit(EXIT_SUCCESS);
            default:
                exit(EXIT_FAILURE);
        } 
        if(parsed)
            break;
    }

    // If called without flags but with text
    if(!parsed && argc > 1) {
        op = ADD_ITEM;
        item = malloc((argc - arg_index - 1) * sizeof(*item));
        for (int i = arg_index + 1; i < argc; i++) {
            item[item_length] = strdup(argv[i]);
            item[item_length] = (i < argc - 1) ? strcat(item[item_length], " ") : strcat(item[item_length], "\n");
            item_length++;
        }
    }

    return (Arguments){op, item, item_length, itemid, listid};
}
