#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#ifndef HTML_H
#define HTML_H

char *Loadhtml(char *direc);

char *Loadhtml(char *direc)
{
    char *fp = malloc(10000);
    int contador = 0;
    DIR *dir;
    struct dirent *file;
    dir = opendir(direc); // abrir la carpeta

    // generar el html
    strcat(fp, "<html>\n");
    strcat(fp, " <head>\n");
    strcat(fp, "  <title>Machi y Tilin</title>\n");
    strcat(fp, " </head>\n");
    strcat(fp, " <body>\n");
    strcat(fp, "  <h3><span style='color:red'>FOLDERS</span></h3>\n");
    strcat(fp, "  <ol>\n");

    while ((file = readdir(dir)))
    {
        if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        char temp[1000];
        strcpy(temp, "   <li><a href = '/home' target = '_blank' style='text-decoration:none'>");
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

#endif
