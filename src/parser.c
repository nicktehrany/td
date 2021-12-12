#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include<stdbool.h>
#include <string.h>

Arguments parse(int argc, char **argv) {
    Operation op = list_items; // By default if no other flag, list items
    char **item;
    int item_length = 0; // the number of char* in the **item
    char *itemid;
    char val;
    int opt;
    bool parsed = false;
    int arg_index = 0;
      
    while((opt = getopt(argc, argv, "hla:f:d:")) != -1) 
    { 
        arg_index++;
        switch(opt) 
        { 
            case 'a':
                op = add_item;
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
                op = finish_item;
                itemid = optarg; 
                parsed = true;
                break;
            case 'd':
                op = delete_item;
                itemid = optarg; 
                parsed = true;
                break;
            case 'l':
                op = list_items; // TODO also have different lists
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
        op = add_item;
        item = malloc((argc - arg_index - 1) * sizeof(*item));
        for (int i = arg_index + 1; i < argc; i++) {
            item[item_length] = strdup(argv[i]);
            item[item_length] = (i < argc - 1) ? strcat(item[item_length], " ") : strcat(item[item_length], "\n");
            item_length++;
            parsed = true;
        }
    }

    return (Arguments){op, item, item_length, itemid};
}
