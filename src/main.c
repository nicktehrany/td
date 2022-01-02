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
    
    for(int i = 0; i < args.item_length; i++)
        free(args.item[i]);

    return 0;
}
