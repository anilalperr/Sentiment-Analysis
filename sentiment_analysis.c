#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "sentiment_analysis.h"

// create a linked list 
txt_lst_t *txtList = NULL;

// adds file to the data structure
void addFile(node_t* newFile) {
    //If txt list is empty 
    if (txtList == NULL) {
        // reserve a memory for this linked list 
        txtList = (txt_lst_t*) malloc(sizeof(txt_lst_t));

        // add it to the beginning of list
        txtList->first_txt = newFile;
        txtList->first_txt->next = NULL;
    } 
    else { 
        // again add it to the beginning of the list
        node_t* prev_first = txtList->first_txt;
        txtList->first_txt = newFile;
        // the previous first will be the second element
        txtList->first_txt->next = prev_first;
    }
}

// Find all txt file in the directory
void addTxtFiles(const char* directory_name) {
    // variables to open a directory and access the contents of this directory
    struct dirent* entry;
    struct stat status;

    DIR* directory = opendir(directory_name);

    // open the directory
    if (directory != NULL) {
        //  for all the files and directories within this directory
        while ((entry = readdir(directory)) != NULL) {
            // if this is the directory's itself and its subdirectory skip it
            if ((strcmp(entry->d_name, ".") == 0) || strcmp(entry->d_name, "..") == 0)  {
                continue;
            }

            //Create path of directory
            char path[strlen(directory_name)+strlen(entry->d_name)+2];
            strcpy(path,directory_name);
            strcat(path,"/");
            strcat(path,entry->d_name);
            
            //Check for status of the file
            if (stat(path,&status) == -1) {
                printf("%s \n",path);
                perror("Failed");
            } 

            // Check if the file is a txt file
            if (strstr(entry->d_name, ".txt") != NULL) {
                //put it in linked list
                node_t *newFile = (node_t *)malloc(sizeof(node_t));
                newFile->txt_name = path;

                // If this txt file is readable, put it into the linked list
                if (status.st_mode & S_IRUSR) {
                    addFile(newFile);
                    printf("Added to list: %s\n",entry->d_name);
                }   
            }

            // if this is a directory, recurse 
            if (S_ISDIR(status.st_mode)) {
                addTxtFiles(path);
            }
        }
    }
    else {  // if no such directory exists print a message
        fprintf(stderr, "Failed to open directory: no such file or directory\n");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char** argv) {
    // Check number of argument
    if (argc != 2) {
        fprintf(stderr, "Please enter exactly one argument. Usage: ./sentiment_analysis [directory name]\n");
    } 

    // access the name of directory
    const char* directory_name = argv[1];

    // add all the txt files in this directory
    addTxtFiles(directory_name);

    // if the list is empty, exit the program
    if (txtList == NULL) {
        printf("There is no readable txt file in this directory\n.");
        exit(2);
    }

  return 0;
}