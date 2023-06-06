#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Parser_H
#define Parser_H

char *Back(char *path); // direccion anterior

char *Back(char *path)
{   
    if(strcmp(path, "/home") == 0)
        return path;
        
    int length = strlen(path);
    int slash = 0;

    for (int i = length-1; i >= 0; i--)
    {
        if(path[i] == '/')
        {
            slash = i;   
            break;
        }
    }

    char *newpath = malloc(sizeof(char)*(slash));

    for (int i = 0; i < slash; i++)
        newpath[i] = path[i];
    
    for(int i = slash; i < strlen(newpath); i++)
        newpath[i] = NULL;

    return newpath;
}

#endif