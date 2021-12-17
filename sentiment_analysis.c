#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "sentiment_analysis.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

// create a linked list
txt_lst_t *txtList = NULL;

// adds file to the data structure
void addFile(node_t *newFile) {
    //If txt list is empty
    if (txtList == NULL) {
        // reserve a memory for this linked list
        txtList = (txt_lst_t *)malloc(sizeof(txt_lst_t));

        // add it to the beginning of list
        txtList->first_txt = newFile;
        txtList->first_txt->next = NULL;
        txtList->length = 1;
    }
    else {
        // again add it to the beginning of the list
        node_t *prev_first = txtList->first_txt;
        txtList->first_txt = newFile;
        // the previous first will be the second element
        txtList->first_txt->next = prev_first;
        txtList->length++;
    }
}

// Find all txt file in the directory
void addTxtFiles(const char *directory_name) {
    // variables to open a directory and access the contents of this directory
    struct dirent *entry;
    struct stat status;

    DIR *directory = opendir(directory_name);

    // open the directory
    if (directory != NULL) {
        //  for all the files and directories within this directory
        while ((entry = readdir(directory)) != NULL) {
            // if this is the directory's itself and its subdirectory skip it
            if ((strcmp(entry->d_name, ".") == 0) || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            //Create path of directory
            char *path = (char *)malloc((strlen(directory_name) + strlen(entry->d_name) + 2) * (sizeof(char)));

            strcpy(path, directory_name);
            strcat(path, "/");
            strcat(path, entry->d_name);

            //Check for status of the file
            if (stat(path, &status) == -1) {
                printf("%s \n", path);
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
                }
            }

            // if this is a directory, recurse
            if (S_ISDIR(status.st_mode)) {
                addTxtFiles(path);
            }
        }
    }
    else { // if no such directory exists print a message
        fprintf(stderr, "Failed to open directory: no such file or directory\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    // Check number of argument
    if (argc != 2) {
        fprintf(stderr, "Please enter exactly one argument. Usage: ./sentiment_analysis [directory name]\n");
    }

    // access the name of directory
    const char *directory_name = argv[1];

    // add all the txt files in this directory
    addTxtFiles(directory_name);

    // if the list is empty, exit the program
    if (txtList == NULL) {
        printf("There is no readable txt file in this directory\n.");
        exit(2);
    }

    // array that stores he ids of child proceses
    pid_t processIds[txtList->length];

    // id index to store ids above
    int idIndex = 0;

    // iterate through the linked list calling fork()
    for (node_t *curTxt = txtList->first_txt; curTxt != NULL; curTxt = curTxt->next) {
        // create a new process
        pid_t rc = fork();

        // if this is parent process
        if (rc < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc == 0) { // if this is child process

            // arguments for execvp function
            char* args[4];
            args[0] = "python3";
            args[1] = "sentiment_analysis.py";
            args[2] = curTxt->txt_name;
            args[3] = NULL;

            printf("%s\n", curTxt->txt_name);

            // execute the python script
            if(execvp("python3", args) == -1){
                printf("execvp error\n");
                exit(EXIT_FAILURE);
            }

            free(args);
        }
        else {
            // add the process id of the parent to the array
            processIds[idIndex] = rc;
            idIndex++;
        }
    }

     // wait for the programs to exit
     for (int i = 0; i < txtList->length; ++i) {
        int status;

        // wait for the process to terminate
        pid_t pid = waitpid(processIds[i], &status, 0);

        //error check
        if (pid == -1) {
            printf("waitpid error occured");
            exit(EXIT_FAILURE);
        }

     }

    return 0;
}
