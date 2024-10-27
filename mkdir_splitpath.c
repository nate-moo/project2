#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

// make directory
// void mkdir(char pathName[]) {
//
//     // TO BE IMPLEMENTED
//     //
//     // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
//
//     if (strlen(pathName) == 0) {
//         printf("MKDIR ERROR: no path provided");
//     }
//
//     char *dirName = "";
//     char *fileName = "";
//
//     struct NODE *dirNode = splitPath(pathName, dirName, fileName);
//
//     // printf("TO BE IMPLEMENTED\n");
//
//     return;
// }

void mkdir(char *pathName)
{

    if ( !strcmp(pathName, "/") )
    {
        puts("MKDIR ERROR: no path provided");
    }
    else
    {
        char * dirName = malloc(strlen(pathName));
        char * baseName = malloc(strlen(pathName));
        struct NODE *directory = splitPath(pathName, baseName, dirName);
        if ( directory )
        {
            for (const struct NODE *temp = directory->childPtr; temp; temp = temp->siblingPtr )
            {
                if ( !strcmp(temp->name, baseName) )
                {
                    printf("MKDIR ERROR: directory %s already exists\n", pathName);
                    return;
                }
            }
            struct NODE *newDir = malloc(sizeof(struct NODE));
            strcpy(newDir->name, baseName);
            newDir->fileType = 'D';
            newDir->childPtr = NULL;
            newDir->siblingPtr = NULL;
            newDir->parentPtr = directory;
            if ( directory->childPtr )
            {
                struct NODE *tNode;
                for ( tNode = directory->childPtr; tNode->siblingPtr; tNode = tNode->siblingPtr )
                    ;
                tNode->siblingPtr = newDir;
            }
            else
            {
                directory->childPtr = newDir;
            }
            printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
        }
    }
}

//
// //handles tokenizing and absolute/relative pathing options
// struct NODE* splitPath(char* pathName, char* baseName, char* dirName){
//
//     // TO BE IMPLEMENTED
//     // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
//     // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
//     // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR
//
//     // YOUR CODE HERE
//     //
//
// 	char * tokenized;
// 	tokenized = strtok(pathName, "/");
// 	char * final = malloc(strlen(pathName));
// 	char * dir = malloc(strlen(pathName));
// 	char * finalDir = malloc(strlen(pathName));
//
// 	// final = "/";
// 	// finalDir = "/";
//
//  	struct NODE* oldNode = root;
//
// 	struct NODE* dirNode = root;
//
// 	while (tokenized != NULL) {
// 		// printf("%s \n", tokenized);
// 		finalDir = final;
// 		final = tokenized;
//
//         oldNode = oldNode;
//         oldNode = dirNode;
//
// 		tokenized = strtok(NULL, "/");
// 		if (tokenized != NULL) {
// 		    //            strcmp(dirNode->childPtr->name, oldNode->name);
// 		    strcat(dir, "/");
// 		    strcat(dir, final);
// 		    if (dirNode->childPtr != NULL && strcmp(dirNode->childPtr->name, final) == 0) {
// 		        printf("Found: %s \n", final);
// 		    } else {
// 		        while (dirNode->siblingPtr != NULL) {
//
// 		            if (strcmp(dirNode->siblingPtr->name, final) == 0) {
// 		                printf("Found %s \n", final);
// 		                break;
// 		            }
//
// 		            dirNode = dirNode->siblingPtr;
// 		        }
//
// 			}
// 		}
//
// 	}
//
//
//
// 	if (strlen(dir) == 0 && pathName[0] == '/') strcat(dir, "/");
//
// 	printf("%s \n", pathName);
// 	printf("%d \n", (int)strlen(pathName));
//
// 	dirName = dir;
// 	baseName = final;
//
//     if (dirNode->childPtr == NULL) {
//         printf("ERROR: directory %s does not exist \n", dirName);
//     }
//
// 	printf("finalDir: %s \n", finalDir);
// 	printf("dirName: %s \n", dirName);
// 	printf("baseName: %s \n", baseName);
//
//
//
// 	return NULL;
// }

struct NODE *splitPath(char *pathName, char *baseName, char *dirName)

{
    int iterVar1;
    size_t strLength;
    struct NODE *directory;

    int finalSlashIndex = -1;
    for (int i = 0; strLength = strlen(pathName), i < strLength - 1; i++) {
        if (pathName[i] == '/') {
            finalSlashIndex = i;
        }
    }
    if (finalSlashIndex == -1) {
        *dirName = (char)NULL;
        strcpy(baseName, pathName);
    } else {
        strncpy(dirName, pathName, finalSlashIndex);
        dirName[finalSlashIndex] = (char)NULL;
        strcpy(baseName, pathName + finalSlashIndex + 1);
    }
    if (*pathName == (char)NULL || *pathName == '/') {
        struct NODE *current;
        directory = root;
        char *token = strtok(dirName, "/");
        while (token != NULL) {
            for (current = directory->childPtr; current != NULL; current = current->siblingPtr) {
                iterVar1 = strcmp(current->name, token);
                if (iterVar1 == 0) {
                    if (current->fileType != 'D') {
                        printf("ERROR: directory %s does not exist\n", token);
                        return NULL;
                    }
                    directory = current;
                    break;
                }
            }
            if (current == NULL) {
                printf("ERROR: directory %s does not exist\n", token);
                return NULL;
            }
            token = strtok(NULL, "/");
        }
    } else {
        struct NODE *current_1;
        directory = cwd;
        char *token_1 = strtok(dirName, "/");
        while (token_1 != NULL) {
            for (current_1 = directory->childPtr; current_1 != NULL; current_1 = current_1->siblingPtr) {
                iterVar1 = strcmp(current_1->name, token_1);
                if (iterVar1 == 0) {
                    if (current_1->fileType != 'D') {
                        printf("ERROR: directory %s does not exist\n", token_1);
                        return NULL;
                    }
                    directory = current_1;
                    break;
                }
            }
            if (current_1 == NULL) {
                printf("ERROR: directory %s does not exist\n", token_1);
                return NULL;
            }
            token_1 = strtok(NULL, "/");
        }
    }

    // printf("BaseName: %s \n", baseName);
    // printf("DirName: %s \n", dirName);
    return directory;
}
