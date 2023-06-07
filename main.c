#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "html.h"
#include "parser.h"
#include "GETRequest.h"

void launch(struct Server *server, char *root_directory)
{
    printf("[SERVER]: Escuchando en el puerto %d... \n", server -> port);
    
    char open_folder[1000];

    int address_lenght = sizeof(server -> address);
    int new_socket = accept(server -> socket, (struct sockaddr *)&server -> address, 
        (socklen_t *)&address_lenght);
    
    char *html = Loadhtml(root_directory);

    send(new_socket, header, strlen(header), 0);
    send(new_socket, html, strlen(html), 0);
    close(new_socket);
    struct GETRequest request;

    while(1)
    {
        new_socket = accept(server -> socket, (struct sockaddr *)&server -> address, 
        (socklen_t *)&address_lenght);   

        read(new_socket, open_folder, sizeof(open_folder)); // leer la solicitud
        request = get_request_constructor(open_folder);
        
        if (strlen(request.URI) > 1) // si pidio algo
        {
            // enviar el nuevo html
            html = Loadhtml(request.URI);
            send(new_socket, header, strlen(header), 0);
            send(new_socket, html, strlen(html), 0);

            // limpio el buffer
            strcpy(open_folder, "");
        }

        // cerrar la conexion
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
