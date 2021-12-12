#include "td.h"

int main(int argc, char *argv[]) {
    Arguments args = parse(argc, argv);
    
    switch (args.op) {
        case ADD:
            add(&args);
            break;
        case FINISH:
            finish(&args);
            break;
        case LIST:
            list(&args);
            break;
        case EDIT:
            edit(&args);
            break;
    }
    // Testing
    /* printf("Op: %d Len: %d NumItems: %d ID: %s\n", args.op, args.item_length, args.num_items, args.itemid); */
    /* for(int i = 0; i < args.item_length; i++) */
    /*     printf("%s", args.item[i]); */

    // TODO cleanup all mallocs
    return 0;
}
