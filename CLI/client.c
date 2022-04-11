#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include "client.h"
#include "CLI.h"

Commands_s commands[] = {
    { "connect", "Command is for connecting", &connecting },
    { "disconnect", "Command is for disconnecting", &disconnect },
    { "get_time", "Command gives current time", &get_time },
    { "prompt", "Choosing a new prompt", &prompt }
};

int connected = 0;
int listening = -2;

void connecting(char **in, int length) {
    if (length == 3) {
        if (listening != -2) {
            printf(" Is already connected.\n");
            return;
        }
        int port = atoi(in[2]);
        listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1) {
            printf("Error in connection.\n");
            return;
        }
        char response[MAX_SIZE];
        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        int con = connect(listening, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        if (con == -1) {
            printf("Error in connection.\n");
            return;
        }

        printf(" Connecting to port: %s, ip_address: %s\n", in[2], in[1]); 
        connected = 1;
    } else {
        printf(" Error: No port or ip_address was given.\n");
    }
}

void disconnect(char **in, int length) {
    if (length == 1 && connected == 1) {
        close(listening);
        printf(" Disconnected from the server.\n");
    } else {
        printf(" Error: Wrong use of command. No argument needed.\n");
    }
}

void get_time(char **in, int length) {
    if (length == 1) {
        printf(" Getting current time\n");
    } else {
        printf(" Error: Wrong use of command. No argument needed.\n");
    }
}

void prompt(char **in, int length) {
    if (length == 2) {
        strcpy(prompt_, in[1]);
    } else {
        printf(" Error: Wrong use of command. No prompt was given.\n");
    }
}

int main() {
    char *input = (char*)malloc(MAX_SIZE);
    strcpy(prompt_, ">");

    while (1) {
        printPrompt(prompt_);

        fgets(input, MAX_SIZE, stdin);
        if (strlen(input) > 1) {
            runCLI(commands, input);
        }    
    }
    free(input);
}

