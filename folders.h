#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// informacion de las carpetas
#include <sys/stat.h>

#ifndef Folders_H
#define Folders_H

int Len(char *direc); // cantidad de archivos de una carpeta
long Size(char *direc); // peso de cualquier folder
long SizeOther(char *direc); // peso de archivos que no son carpetas
long SizeFolder(char *direc); // peso de las carpetas
int IsFolder(char *direc); // verificar si una direccion coincide con una carpeta

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

long Size(char *direc)
{
    if(IsFolder(direc))
        return SizeFolder(direc);

    return SizeOther(direc);
}

long SizeFolder(char *direc) // itera por todas las carpetas y suma el peso de los subarchivos
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

            total_size += SizeFolder(full_path);
        }

        else
            total_size += info.st_size;
    }

    closedir(dir);
    return total_size;
}

long SizeOther(char *direc)
{
    struct stat fileStat;
    int temp = stat(direc, &fileStat);
   return fileStat.st_size;
}

int IsFolder(char *direc)
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir(direc);

    if (dir != NULL) 
    {
        closedir(dir);
        return 1;
    } 

    return 0;
}

#endif
