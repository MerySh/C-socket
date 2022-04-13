#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include "client.h"
#include "CLI.h"

#define MAX_CLIENTS 5
#define MAX_SIZE 100

Commands_s commands[] = {
    { "disconnect", "Command is for disconnecting" },
    { "get_time", "Command gives current time" },
    { "get_clients_info", "Command gives clients information" },
    { "get_clients_list", "Command gives clients list" }
};

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

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    int binding = bind(listening, (struct sockaddr*)&server_address, sizeof(server_address));
    if (binding == -1) {
        printf("Error in binding.\n");
        exit(1);
    }

    if (listen(listening, MAX_CLIENTS) == 0) {
        printf("Listening for the client...\n");
    } else {
        printf("Error in listening.\n");
        exit(1);
    }

    int client_socket;
    struct sockaddr_in new_address;
    char *buffer1 = (char*)malloc(MAX_SIZE);
    char *buffer2 = (char*)malloc(MAX_SIZE);
    
    while (1) {
        /*
        printPrompt("$");

        char *input = (char*)malloc(MAX_SIZE);
        fgets(input, MAX_SIZE, stdin);
        if (strlen(input) > 1) {
            runCLI(commands, input);
        }
        */
 
        client_socket = accept(listening, NULL, NULL);  
        if (client_socket == -1) {
            exit(1);
        }
 
        char port[MAX_SIZE];
        char ip_addr[MAX_SIZE];
        recv(client_socket, buffer1, 2048, 0);
        for (int i = 0; i < strlen(buffer1); ++i) {
            if (buffer1[i] != ' ') {
                ip_addr[i] = buffer1[i];   
            } else {
                int k = 0;
                for (int j = i+1; j < strlen(buffer1); ++j) {
                    port[k++] = buffer1[j];
                }
                break;
            }
        }
        if (!strncmp(argv[1], port, 4)) {            
            printf("Connection accepted from %s:%s\n", ip_addr, port); 
        }

        while (1) {
            recv(client_socket, buffer2, 2048, 0);
            if (!strncmp(buffer2, "disconnect", 10)) {
                printf("Disconnected from %s:%s\n", ip_addr, port);
                break;
            } else if (!strncmp(buffer2, "get_time", 8)) {
                time_t current_time = time(NULL);
                char buff[MAX_SIZE];
                strftime(buff, MAX_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&current_time));
                send(client_socket, &buff, MAX_SIZE, 0);
            }
        }
    }
    free(buffer1);
    free(buffer2);
}
