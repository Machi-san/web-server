#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

// sockets
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "parser.h"

#ifndef Download_H
#define Download_H

void SendDownload(char *direc, int fdc); // descargar archivos que pide el usuario
char header_download[] = "HTTP/1.1 200 OK\r\n"; // header de la descarga de archivos

void SendDownload(char *direc, int fdc)
{
    // estructuras auxiliares
    int fd;
    off_t offset = 0;
    struct stat file_stat;
    int sent_bytes = 0;

    // Abrir el archivo que se va a enviar
    fd = open(direc, O_RDONLY);

    // Obtener información sobre el archivo
    if (fstat(fd, &file_stat) < 0) {
        perror("Error al obtener información del archivo");
        exit(EXIT_FAILURE);
    }

    // Enviar la cabecera HTTP al usuario
    send(fdc, header_download, strlen(header_download), 0);

    // Enviar el archivo al usuario
    sent_bytes = sendfile(fdc, fd, &offset, file_stat.st_size);
  
    // Cerrar el archivo
    close(fd);
}

#endif