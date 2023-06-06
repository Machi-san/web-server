#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#ifndef HTML_H
#define HTML_H

#include "parser.h"

char *Loadhtml(char *direc); // generar el html
char header[] = "HTTP/1.1 200 OK\r\n Content-Type: text/html \r\n\r\n\r\n"; // cabecera http
int Len(char *direc); // cantidad de archivos en el directorio

char *Loadhtml(char *direc)
{
    // abrir la carpeta
    DIR *dir;
    struct dirent *file;
    dir = opendir(direc);

    // manejar el espacio en memoria
    int size = Len(direc);
    char *fp = malloc(1000 * size * sizeof(char));

    // generar el html
    strcpy(fp, "");
    strcat(fp, "<html>\n");
    strcat(fp, " <head>\n");
    strcat(fp, "  <title>Machi y Tilin</title>\n");
    strcat(fp, " </head>\n");
    strcat(fp, " <body>\n");
    strcat(fp, "  <h3><span style='color:blue'>FOLDERS</span></h3>\n");
    strcat(fp, "  <ol>\n");
    strcat(fp, "   <li><a href = '");
    strcat(fp, Back(direc));
    strcat(fp, "' style='text-decoration:none; color:red'>Atras</a></li>\n");
    while ((file = readdir(dir)))
    {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        char temp[1000];
        strcpy(temp, "   <li><a href = '");
        strcat(temp, direc);
        strcat(temp, "/");
        strcat(temp, file->d_name);
        strcat(temp, "'");
        strcat(temp, " style='text-decoration:none; color:green'>");
        strcat(temp, file->d_name);
        strcat(temp, "</a></li>\n");
        strcat(fp, temp);
    }

    strcat(fp, "  <ol>\n");
    strcat(fp, " </body>\n");
    strcat(fp, "</html>\n");
    closedir(dir);
    return fp;
}

int Len(char *direc)
{
    // abrir la carpeta
    DIR *dir;
    struct dirent *file;
    dir = opendir(direc);

    int len = 0;

    while ((file = readdir(dir)))
        len++;

    closedir(dir);
    return len;
}

#endif
