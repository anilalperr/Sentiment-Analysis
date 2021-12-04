#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

//Helpers to Implement
//*isReadable (see line 34)

// Linked list for txt file
typedef struct node
{
    char *txt_name;
    struct node *next;
} node_t;

// Linked list of txt file
typedef struct txt_lst 
{
    node_t *first_txt;
}txt_lst_t;

// Find all txt file in the directory
void getTxtFiles(const char* directory_name, txt_lst_t* txtList) {
    printf("entered get txt file\n");

    // variables to open a directory and access the contents of this directory
  
    struct dirent* entry;
    struct stat status;
    int isReadable = 0;


    DIR* directory = opendir(directory_name);

    // open the directory
    if (directory != NULL) {
        printf("opened directory\n");
        //  for all the files and directories within this directory
        while ((entry = readdir(directory)) != NULL) {
            printf("entered the while loop\n");

            //Create path of directory
            char path[strlen(directory_name)+strlen(entry->d_name)+2];
            path[0] = '\0';
            strcat(path,directory_name);
            strcat(path,"/");
            strcat(path,entry->d_name);
            printf("entry name is %s\n", entry->d_name);

            //Check for status of the file
            if (stat(path,&status) == -1) {
                printf("%s \n",path);
                perror("Failed");
            } 


            // Check if the file is a txt file
            if (strstr(".txt", entry->d_name) != NULL) {
                //put in linked list
                node_t *newFile = (node_t *)malloc(sizeof(node_t));
                newFile->txt_name = entry->d_name;

                //If txt list is empty (first element)
                if (txtList->first_txt == NULL) {

                    newFile->next = txtList->first_txt;
                    txtList->first_txt->next = newFile;
                    newFile->next = NULL;
                } else { //if there is at least one file in the list, 
                    node_t *current = txtList->first_txt;

                    while (current->next != NULL) {
                        current = current->next;
                    }

                    newFile->next = current->next;
                    current->next = newFile;
                }

                printf("%s\n",entry->d_name);


            }

               
            // create a struct to store the information about file

           // access the path to the file
            //char* subDirectory = getSubDirectory(directory_name, dirContent->d_name);

            // access the file permissions [IMPLEMENT THE HELPER!!!!!!]
            //boolean readable = isReadable(fileInfo.st_mode, subDirectory);

            // Find all txt files, put them in linked list
            if (status.st_mode == S_IRUSR) {
                isReadable = 1;
            } else {
                isReadable = 0;
            }
            //// Find txt file

            /// check readability


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

    //create a linked list 
    txt_lst_t *txtList; 
    txtList->first_txt = NULL;

    getTxtFiles(directory_name, txtList);


    

  return 0;
}