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

int main(int argc, char **argv){
    // checking if user inputs the port
    if (argc != 2){
        printf("No port was given.\nPlease write: ./server <port>\n");
        exit(1);
    }

    // reading port from the file
    FILE* fp = fopen("activePorts.txt", "r");
    if (fp == NULL) {
        printf("Could not open file.\n");
        exit(1);
    }

    char buff[256];
    while (fgets(buff, 256, fp)) {
        if (strcmp(argv[1], buff)) {
            printf("This port is not active.\n");
            exit(1);
        }
    }
    fclose(fp);

    // checking if clients are not more than 5
    FILE* fp2 = fopen("clientsCount.txt", "r");
    char ch = fgetc(fp2);
    if (atoi(&ch) == MAX_CLIENTS) {
        perror("Server is overloaded. Try again later.\n");
        exit(0);
    }

    int port = atoi(argv[1]); // Converting string to an integer
    
    // creating a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        perror("Error in connection.\n");
        exit(1);
    }

    char response[30];
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // connecting 
    int con = connect(listening, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (con == -1) {
        perror("Error in connection.\n");
        exit(1);
    }
    
    printf("Connected to the server\n");

    // after everything is okay
    char buffer[2048];
    while (1) { 
            printf("Client: ");
            scanf("%s", &buffer[0]);
            send(listening, buffer, strlen(buffer), 0);

            if (strcmp(buffer, ":disconnect") == 0) {
                close(listening);
                printf("Disconnected from server.\n");
                exit(1);
            } else if (strcmp(buffer, ":get_time") == 0) {
                recv(listening, response, 29, 0);
                printf("Time from server: %s\n", response);
                continue;
            }

            if (recv(listening, buffer, 2048, 0) == -1) {
                perror("Error in receiving data.\n");
                exit(1);
            } else {
                printf("Server: %s\n", buffer);
            }
    }

    recv(listening, response, 29, 0);
    printf("Time from server: %s\n", response);

    return 0;
}
