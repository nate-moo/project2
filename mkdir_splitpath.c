#include <stdio.h>
#include <string.h>
#include "types.h"

extern struct NODE *root;
extern struct NODE *cwd;

void mkdir(char *pathName) {

    if (!strcmp(pathName, "/")) {
        puts("MKDIR ERROR: no path provided");
    } else {
        char *dirName = malloc(strlen(pathName));
        char *baseName = malloc(strlen(pathName));
        struct NODE *directory = splitPath(pathName, baseName, dirName);
        if (directory) {
            for (const struct NODE *temp = directory->childPtr; temp; temp = temp->siblingPtr) {
                if (!strcmp(temp->name, baseName)) {
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
            if (directory->childPtr) {
                struct NODE *tNode;
                for (tNode = directory->childPtr; tNode->siblingPtr; tNode = tNode->siblingPtr);
                tNode->siblingPtr = newDir;
            } else {
                directory->childPtr = newDir;
            }
            printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
        }
    }
}

struct NODE *splitPath(char *pathName, char *baseName, char *dirName) {
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
        *dirName = (char) NULL;
        strcpy(baseName, pathName);
    } else {
        strncpy(dirName, pathName, finalSlashIndex);
        dirName[finalSlashIndex] = (char) NULL;
        strcpy(baseName, pathName + finalSlashIndex + 1);
    }
    if (*pathName == (char) NULL || *pathName == '/') {
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

    return directory;
}
