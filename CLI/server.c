#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_CLIENTS 5

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error: no port was given.\nPlease write: ./server <port>\n");
        exit(1);
    }

    int port = atoi(argv[1]);

    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        printf("Error in connection.\n");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    int binding = bind(listening, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (binding == -1) {
        printf("Error in binding.\n");
        exit(1);
    }
    printf("Bind to port: %d\n", port);

    if (listen(listening, MAX_CLIENTS) == 0) {
        printf("Listening for the client...\n");
    } else {
        printf("Error in listening.\n");
        exit(1);
    }

    int client_socket;
    struct sockaddr_in newAddress;

    while (1) {
        client_socket = accept(listening, NULL, NULL);  
        if (client_socket == -1) {
            exit(1);
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));
    }
}
