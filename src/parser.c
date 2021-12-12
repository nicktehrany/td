#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

Arguments parse(int argc, char **argv) {
    Operation op = LIST; // By default if no other flag, list items
    char **item;
    int item_length = 0; // the number of char* in the **item
    char *itemid = NULL;
    int num_items = 1;
    int opt;
    bool parsed = false;
    int arg_index = 0;

    // WHat we need:
    // no flag for adding, just td something to add
    // no flag for listing just td
    // -e for edit (replace or sed like /match/replace)
    // -f [id*], mark as finished id or multiple ids

    static struct option long_options[] = {
        {"finish", required_argument , NULL, 'f'},
        {"edit", required_argument, NULL, 'e'},
        {"help", no_argument , NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    while((opt = getopt_long(argc, argv, "hf:e:", long_options, NULL)) != -1) 
    { 
        arg_index++;
        switch(opt) 
        { 
            case 'f': // TODO finish multiple at once
                op = FINISH;
                itemid = optarg; 
                parsed = true;
                break;
            case 'e':
                op = EDIT; // TODO allow sed like subs
                itemid = optarg;
                item = malloc((argc - arg_index - 1) * sizeof(*item));
                for (int i = arg_index + 2; i < argc; i++) {
                    item[item_length] = strdup(argv[i]);
                    item_length++;
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
    if(!parsed && argc > 1) { // TODO multiple items seperated with ,
        op = ADD;
        item = malloc((argc - arg_index - 1) * sizeof(*item));
        for (int i = arg_index + 1; i < argc; i++) {
            item[item_length] = strdup(argv[i]);
            item_length++;
        }
    }

    return (Arguments){op, item, item_length, num_items, itemid};
}
