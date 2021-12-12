#include "td.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int get_next_id() {
    char pwd[FILENAME_MAX];
    getcwd(pwd, FILENAME_MAX);
    
    char path[strlen(pwd) + 7];
    strcpy(path, strcat(pwd, "/.todos"));
    FILE *fp = fopen(path, "r");
    int lines = 0;
    char c;

    while(!feof(fp)) {
        c = fgetc(fp);
        if(c == '\n')
            lines++;
    }

    return lines;
}

int add(Arguments *args) {
    char pwd[FILENAME_MAX];
    getcwd(pwd, FILENAME_MAX);
    
    char path[strlen(pwd) + 7];
    strcpy(path, strcat(pwd, "/.todos"));
    FILE *fp = fopen(path, "a+");
    if(fp == NULL) {
        LOG(ERROR, EXIT_FAILURE, "Failed to open file");
    }
    for(int i = 0; i < args->num_items; i++) {
        fprintf(fp, "%d - ", get_next_id());
        for(int j = 0; j < args->item_length; j++)
            fprintf(fp, "%s ", args->item[j]);
        fprintf(fp, "\n");
    }

    fclose(fp);
        
    return 0;
}

int list(Arguments *args) {
    char pwd[FILENAME_MAX];
    getcwd(pwd, FILENAME_MAX);
    
    char path[strlen(pwd) + 7];
    strcpy(path, strcat(pwd, "/.todos"));
    FILE *fp = fopen(path, "r");
    if(fp == NULL) {
        LOG(ERROR, EXIT_FAILURE, "Failed to open .todos file");
    }
    
    char c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
  
    fclose(fp);

    return 0;
}

int finish(Arguments *args) {
    char pwd[FILENAME_MAX];
    getcwd(pwd, FILENAME_MAX);
    
    char path[strlen(pwd) + 7];
    strcpy(path, strcat(pwd, "/.todos"));
    FILE *fp = fopen(path, "r");
    if(fp == NULL) {
        LOG(ERROR, EXIT_FAILURE, "Failed to open .todos file");
    }
    
    char data[MAX_LINES][LINE_SIZE];
    int index = 0;
    while(fgets(data[index], LINE_SIZE, fp)) {
        if(strncmp(data[index], args->itemid, strlen(args->itemid)))
            index++;
    }

    fclose(fp);
    fp = fopen(path, "w"); // Empty the file and we write the data without the item.
    for(int i = 0; i < index; i++)
        fprintf(fp, "%s", data[i]);
    fclose(fp);

    return 0;
}

int edit(Arguments *args) {
    char pwd[FILENAME_MAX];
    getcwd(pwd, FILENAME_MAX);
    
    char path[strlen(pwd) + 7];
    strcpy(path, strcat(pwd, "/.todos"));
    FILE *fp = fopen(path, "r");
    if(fp == NULL) {
        LOG(ERROR, EXIT_FAILURE, "Failed to open .todos file");
    }
    
    char data[MAX_LINES][LINE_SIZE];
    int index = 0;
    while(fgets(data[index], LINE_SIZE, fp)) {
        if(!strncmp(data[index], args->itemid, strlen(args->itemid))) {
            char *new_data = malloc(LINE_SIZE * sizeof(char *));
            char id[ID_SIZE + 3];
            sprintf(id, "%d - ", get_next_id());
            strcat(new_data, id);
            for(int i = 0; i < args->num_items; i++) {
                for(int j = 0; j < args->item_length; j++) {
                    strcat(new_data, args->item[j]);
                    strcat(new_data, " ");
                }
                strcat(new_data, "\n");
            }
            strcpy(data[index], new_data);
            free(new_data);
        }
        index++;
    }

    fclose(fp);
    fp = fopen(path, "w"); // Empty the file and rewrite the data without the item.
    for(int i = 0; i < index; i++)
        fprintf(fp, "%s", data[i]);
    fclose(fp);
    
    return 0;
}
