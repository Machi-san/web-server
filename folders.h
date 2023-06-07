#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// informacion de las carpetas
#include <sys/stat.h>

#ifndef Folders_H
#define Folders_H

int Len(char *direc); // cantidad de archivos de una carpeta
long Size(char* direc); // peso de una carpeta

int Len(char *direc)
{
    // abrir la carpeta
    DIR *dir;
    struct dirent *file;
    dir = opendir(direc);

    int len = 0;

    while ((file = readdir(dir)))
    {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;

        len++;
    }

    closedir(dir);
    return len;
}

// itera por todas las carpetas y suma el peso de los subarchivos
long Size(char* direc) 
{
    struct dirent *entry;
    DIR *dir = opendir(direc);
    long total_size = 0;

    if (dir == NULL) 
        return 0;

    while ((entry = readdir(dir)) != NULL) 
    {
        char full_path[1024];
        struct stat info;
        snprintf(full_path, sizeof(full_path), "%s/%s", direc, entry->d_name);

        if (stat(full_path, &info) == -1) 
            continue;

        if (S_ISDIR(info.st_mode)) 
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
                continue;
            
            total_size += Size(full_path);
        }
        
         else 
            total_size += info.st_size;
    }

    closedir(dir);
    return total_size;
}

#endif
