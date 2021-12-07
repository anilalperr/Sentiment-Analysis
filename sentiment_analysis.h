#include <stdlib.h>

// Linked list for txt file
typedef struct node {
    char *txt_name;
    struct node *next;
} node_t;

// Linked list of txt file
typedef struct txt_lst {
    node_t *first_txt;
    int length;
}txt_lst_t;

void addFile(node_t* newFile);

void addTxtFiles(const char* directory_name);