#include "parser.h"

int main(int argc, char *argv[]) {
    Arguments args = parse(argc, argv);
    
    // Testing
    printf("Op: %d Len: %d ID: %s\n", args.op, args.item_length, args.itemid);
    for(int i = 0; i < args.item_length; i++)
        printf("%s", args.item[i]);

    return 0;
}
