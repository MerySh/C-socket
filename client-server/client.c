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

#define MAX_SIZE 100
#define MAX_COMMANDS 4

Commands_s commands[] = {
    { "connect", "Command is for connecting. connect <ip_addr> <port>", &connecting },
    { "disconnect", "Command is for disconnecting", &disconnecting },
    { "get_time", "Command gives current time", &get_time },
    { "prompt", "Choosing a new prompt", &set_prompt }
};

int connected = 0;
int listening = -2;

/*
 * Connects client to a server, if that is an error during connecting function returns,
 * if all completed successfully function prints connecting port and ip address
 */
void connecting(char **in, int length) {
    if (length == 3) {
        if (connected == 1) {
            printf(" Is already connected.\n");
            return;
        }
        int port = atoi(in[2]);
        listening = socket(AF_INET, SOCK_STREAM, 0);
        if (listening == -1) {
            printf(" Error in connection.\n");
            return;
        }
 
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        int con = connect(listening, (struct sockaddr*)&server_address, sizeof(server_address));
        if (con == -1) {
            printf(" Error in connection.\n");
            return;
        }
 
        char *text = (char*)malloc(MAX_SIZE);
        char *response = (char*)malloc(MAX_SIZE);
        strcat(text, in[1]);
        strcat(text, " ");
        strcat(text, in[2]);
        send(listening, text, strlen(text), 0);
        
        printf(" Connecting to port: %s, ip_address: %s\n", in[2], in[1]); 
        connected = 1;
        
        free(text);
        free(response);
    } else {
        printf(" Error: No port or ip_address was given.\n");
    }
}

/*
 * Disconnects from server, closes it and prints a message if there was a connection,
 * if there was not then prints an error 
 */
void disconnecting(char **in, int length) {
    if (length == 1) {
        if (connected == 1) {
            send(listening, in[0], strlen(in[0]), 0);
            close(listening);
            connected = 0;
            printf(" Disconnected from the server.\n");
        } else {
            printf(" There is no connection to disconnect.\n");
        }
    } else {
        printf(" Error: Wrong use of command. No argument needed.\n");
    }
}

/*
 * Sends the server a request and receives current time with according format
 */
void get_time(char **in, int length) {
    char *response = (char*)malloc(MAX_SIZE);

    if (length == 1) {
        if (connected == 1) {
            send(listening, in[0], strlen(in[0]), 0);
            recv(listening, response, MAX_SIZE, 0);
            printf(" Current time is %s\n", response);
        } else {
            printf(" There is no connection to server.\n");
        }
    } else {
        printf(" Error: Wrong use of command. No argument needed.\n");
    }
    free(response);
}

/*
 * Sets new prompt to CLI
 */
char prompt[MAX_SIZE];
void set_prompt(char **in, int length) {
    if (length == 2) {
        strcpy(prompt, in[1]);
    } else {
        printf(" Error: Wrong use of command. No prompt was given.\n");
    }
}

int main() {
    char *input = (char*)malloc(MAX_SIZE);
    strcpy(prompt, ">");

    while (1) {
        print_prompt(prompt);
        fgets(input, MAX_SIZE, stdin);

        if (strlen(input) > 1) {
            int commands_count = sizeof(commands) / sizeof(commands[0]);
            run_cli(commands, commands_count, input);
        }    
    }
    free(input);
}

