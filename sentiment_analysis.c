#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Helpers to Implement
//*isReadable (see line 34)

// Linked list for txt file
typedef struct node
{
    char *txt_name;
    node_t *next;
} node_t;

// Linked list of txt file
typedef struct txt_lst 
{
    node_t *first_txt;
}

// Find all txt file in the directory
void getTxtFiles(const char* directory_name) {

    // variables to open a directory and access the contents of this directory
    DIR* directory;
    struct dirent* dirContent;

    // open the directory
    if ((directory = opendir(directory_name)) != NULL) {
        //  for all the files and directories within this directory
        while ((dirContent = readdir(directory)) != NULL) {
            // create a struct to store the information about file
            struct stat fileInfo;

            // access the path to the file
            char* subDirectory = getSubDirectory(directory_name, dirContent->d_name);

            // access the file permissions [IMPLEMENT THE HELPER!!!!!!]
            boolean readable = isReadable(fileInfo.st_mode, subDirectory);

            // Find all txt files, put them in linked list


        }

    }
    else {  // if no such directory exists print a message
        fprintf(stderr, "Failed to open directory: no such file or directory\n");
    }

}


int main(int argc, char** argv) {
    
    // Check number of argument
    if (argc != 2) {
        fprintf(stderr, "Please enter exactly one argument. Usage: ./sentiment_analysis [directory name]\n");
    } 

    // access the name of directory
    const char* directory_name = argv[1];

    

  return 0;
}