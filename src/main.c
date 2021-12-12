#include "td.h"

int main(int argc, char *argv[]) {
    Arguments args = parse(argc, argv);
    
    switch (args.op) {
        case ADD_ITEM:
            add_item(&args);
            break;
        case DELETE_ITEM:
            delete_item(&args);
            break;
        case LIST_ITEMS:
            list_items(&args);
            break;
        case FINISH_ITEM:
            finish_item(&args);
            break;
    }
    // Testing
    /* printf("Op: %d Len: %d ID: %s ListID: %s\n", args.op, args.item_length, args.itemid, args.listid); */
    /* for(int i = 0; i < args.item_length; i++) */
    /*     printf("%s", args.item[i]); */

    // TODO cleanup all mallocs
    return 0;
}
