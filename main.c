#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "html.h"
#include "parser.h"
#include "GETRequest.h"
#include "download.h"

void launch(struct Server *server, char *root_directory)
{
    printf("[SERVER]: Escuchando en el puerto %d... \n", server -> port);
    
    char open_folder[1000];
    char *parse = malloc(1000 * sizeof(char));

    int address_lenght = sizeof(server -> address);
    int new_socket = accept(server -> socket, (struct sockaddr *)&server -> address, 
        (socklen_t *)&address_lenght);
    
    SendHtml(root_directory, new_socket);
    close(new_socket);

    while(1)
    {
        new_socket = accept(server -> socket, (struct sockaddr *)&server -> address, 
        (socklen_t *)&address_lenght);   

        int temp = read(new_socket, open_folder, sizeof(open_folder)); // leer la solicitud
        parse = Parse(open_folder); // carpeta a abrir
        
        if (strlen(parse) > 1) // si pidio algo
        {
            // descargar el archivo
            if(IsFolder(parse) == 0)
                SendDownload(parse, new_socket);
            
            // enviar el nuevo html
            else
                SendHtml(parse, new_socket);
            
            // limpio el buffer
            strcpy(open_folder, "");
        }
        close(new_socket);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Uso: %s <puerto> <directorio_raiz>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    char *root_directory = argv[2];

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, port, 10, launch);
    server.launch(&server, root_directory);
}
