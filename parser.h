#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Parser_H
#define Parser_H

int BreakLine(char *string); // identifica el salto de linea
char *Parse(char *string); // parsea la peticion
char *Back(char *path); // direccion anterior

int BreakLine(char *string)
{
    int contador = 0;

    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == '\n')
            break;
        
        contador++;
    }

    return contador;
}

char *Parse(char *string)
{
    char *temp = malloc(1000*sizeof(char));
    int contador = 0;

    for(int i = 4; i < BreakLine(string) - 10; i++)
        temp[contador++] = string[i];
    
    for(int i = contador; i < strlen(temp); i++) // limpiar el buffer
        temp[i] = NULL;
    
    if(strcmp(temp, "/favicon.ico") == 0)
        strcpy(temp, "/"); 

    return temp;
}

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