#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "app.h"
#include "CLI.h"

Commands_s commands[] = {
    { "connect", "Command is for connecting", &connect },
    { "disconnect", "Command is for disconnecting", &disconnect },
    { "get_time", "Command gives current time", &get_time }
};

void connect(char **in) {
    if (strlen(in[1]) && strlen(in[2])) {
        printf(" Connecting to port: %s, ip_address: %s\n", in[2], in[1]); 
    } else {
        printf(" Error: No port or ip_address was given.\n");
    }
}

void disconnect(char **in) {
    if (!strlen(in[1])) {
        printf(" Disconenct\n");    
    } else {
        printf(" Error: Wrong use of command.\n");
    }
}

void get_time(char **in) {
    if (!strlen(in[1])) {
        printf(" Getting current time\n");
    } else {
        printf(" Error: Wrong use of command.\n");
    }
}

int main() {
    char *prompt = "> ";

    char **input = (char**)malloc(MAX_SIZE *sizeof(*input));
    while (1) {
        printPrompt(prompt);
   
        fgets(input, MAX_SIZE, stdin);
        if (strlen(input) > 1) {
            runCLI(commands, input);
        }    
    }
    free(input);
}

