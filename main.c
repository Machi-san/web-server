#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s <puerto> <directorio_raiz>\n", argv[0]);
        return 1;
    }
    
    int port = atoi(argv[1]);
    const char* root_directory = argv[2];
    
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    
    // Crear el socket del servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error al crear el socket del servidor");
        return 1;
    }
    
    // Configurar la dirección del servidor
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);
    
    // Vincular el socket a la dirección del servidor
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error al vincular el socket a la dirección del servidor");
        return 1;
    }
    
    // Escuchar conexiones entrantes
    if (listen(server_socket, 10) == -1) {
        perror("Error al escuchar conexiones entrantes");
        return 1;
    }
    
    printf("Servidor web iniciado. Esperando conexiones...\n");
    
    while (1) {
        // Aceptar una nueva conexión de cliente
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Error al aceptar la conexión del cliente");
            return 1;
        }
        
        // Manejar la solicitud del cliente en un proceso hijo
        if (fork() == 0) {
            close(server_socket);  // El proceso hijo no necesita el socket del servidor
            handle_client_request(client_socket, root_directory);
            return 0;
        } else {
            close(client_socket);  // El proceso padre no necesita el socket del cliente
        }
    }
    
    // Cerrar el socket del servidor
    close(server_socket);
    
    return 0;
}
