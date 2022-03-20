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
static int clientsCount = 0;

int getClientsCount () {
    FILE* fp = fopen("clientsCount.txt", "r");
    char character = fgetc(fp);
    int count = atoi(&character);
    
    return count;
}

int main(int argc, char** argv) {
    // checking if user inputs the port
    if (argc != 2){
        printf("No port was given.\nPlease write: ./server <port>\n");
        exit(1);
    }

    // writing port in a file
    char* fileName = "activePorts.txt";
    FILE* fp = fopen(fileName, "w");
    fprintf(fp, "%s", argv[1]);
    fclose(fp);
    
    int port = atoi(argv[1]); // Converting string to an integer

    // creating a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0); 
    if (listening == -1) {
        perror("Error in connection.\n");
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // binding with port
    int binding = bind(listening, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (binding == -1) {
        perror("Error in binding.\n");
        exit(1);
    }
    printf("Bind to port: %d\n", port);

    // listen
    if (listen(listening, MAX_CLIENTS) == 0) {
        printf("Listening for the client...\n");
    } else {
        perror("Error in listening.\n");
        exit(1);
    }

    // after everything is okay
    int client_socket;
    struct sockaddr_in newAddress;
    char buffer[2048];
    //int clientsCount = 0;

    char* fileName2 = "clientsCount.txt";
    FILE* fp2 = fopen(fileName2, "w");
    fprintf(fp2, "%d", clientsCount);
    fclose(fp2);

    while (1) {
        client_socket = accept(listening, NULL, NULL);
        if (client_socket == -1) {
            exit(1);
        }

        clientsCount = getClientsCount();
        ++clientsCount;
        FILE* fp2 = fopen(fileName2, "w");
        fprintf(fp2, "%d", clientsCount);
        fclose(fp2);

        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));

        pid_t childpid;
        if ((childpid = fork()) == 0) {
            close(listening);

            while (1) {
                recv(client_socket, buffer, 2048, 0);
                if (strcmp(buffer, ":disconnect") == 0) {
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));
                    
                    clientsCount = getClientsCount();
                    --clientsCount;
    
                    FILE* fp2 = fopen(fileName2, "w");
                    fprintf(fp2, "%d", clientsCount);
                    fclose(fp2);
                    break;
                } else if (strcmp(buffer, ":get_time") == 0) {
                    time_t currentTime = time(NULL);
                    char buff[20];
                    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&currentTime));
                    send(client_socket, &buff, 30, 0);
                    printf("Client requested for time.\n");
                } else {
                    printf("Client: %s\n", buffer);
                    send(client_socket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
    close(client_socket);

    return 0;
}
