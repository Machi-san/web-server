#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// informacion de las carpetas
#include <sys/stat.h>

// sockets
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#ifndef HTML_H
#define HTML_H

#include "parser.h"
#include "folders.h"

char *Loadhtml(char *direc); // generar el html
void SendHtml(char *direc, int fdc); // enviar el archivo html
char header[] = "HTTP/1.1 200 OK\r\n Content-Type: text/html \r\n\r\n\r\n"; // cabecera http del archivo html

char *Loadhtml(char *direc)
{
    // manejar el espacio en memoria
    int size = Len(direc);
    char *fp = malloc(1000 * (size + 1) * sizeof(char));
   
    // abrir la carpeta
    DIR *dir;
    struct dirent *file;
    dir = opendir(direc);

    // peso del archivo
    char* filename = malloc(1000 + 1000 * size * sizeof(char));

    // generar el html
    strcpy(fp, "");
    strcat(fp, "<html>\n");
    strcat(fp, " <head>\n");
    strcat(fp, "  <title>Web Server</title>\n");
    strcat(fp, " </head>\n");
    strcat(fp, " <body style='background-color:yellow'>\n");
    strcat(fp, "  <h1 style='width:100%; color:green; border-width:0px; text-align:center'>MyServer</h1>\n");
    strcat(fp, "  <table style='border-collapse:collapse; width:100%'>\n");
    strcat(fp, "   <tr><th style='border:1px solid yellow; color:red; text-align:left'>NAME</th><th style='border:1px solid yellow; color:red; text-align:left'>SIZE</th><tr>\n");
    strcat(fp, "   <tr><td colspan = '2' style='border:1px solid yellow'><a href='");
    strcat(fp, Back(direc));
    strcat(fp, "' style='text-decoration:none; color:blue'>Back</a></td><tr>\n");
    

    while (size > 0 &&(file = readdir(dir)))
    {
        if (file->d_name[0] == '.')
            continue;
        
        strcpy(filename, "");
        strcat(filename, direc);
        strcat(filename, "/");
        strcat(filename, file->d_name);
        char size_kb[10000];
        sprintf(size_kb, "%10f", (float)Size(filename) / (1024 * 1024));          
        
        // filas de table
        char *temp = malloc(10000);
        strcpy(temp, "   <tr><td style='border:1px solid gray'><a href = '");
        strcat(temp, direc);
        strcat(temp, "/");
        strcat(temp, file->d_name);
        strcat(temp, " 'style='text-decoration:none; color:black'>");
        strcat(temp, file->d_name);
        strcat(temp, "</a></td><td style='border:1px solid gray'>");
        strcat(temp, size_kb);
        strcat(temp, " megabytes</td></tr>\n");
        strcat(fp, temp); 
        strcpy(temp, "");
    }
    
    strcat(fp, "  <table>\n");
    strcat(fp, " </body>\n");
    strcat(fp, "</html>\n");
    closedir(dir);
    return fp;
}

void SendHtml(char *direc, int fdc)
{
    char *html = Loadhtml(direc);
    send(fdc, header, strlen(header), 0);
    send(fdc, html, strlen(html), 0);
}

#endif
