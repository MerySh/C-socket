#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "app.h"
#include "CLI.h"

Commands_s commands[] = {
    { "connect", "Command is for connecting", &connect },
    { "disconnect", "Command is for disconnecting", &disconnect },
    { "get_time", "Command gives current time", &get_time },
    { "prompt", "Choosing a new prompt", &prompt }
};

void connect(char **in, int length) {
    if (length == 3) {
        printf(" Connecting to port: %s, ip_address: %s\n", in[2], in[1]); 
    } else {
        printf(" Error: No port or ip_address was given.\n");
    }
}

void disconnect(char **in, int length) {
    if (length == 1) {
        printf(" Disconenct\n");    
    } else {
        printf(" Error: Wrong use of command. No argument nedded.\n");
    }
}

void get_time(char **in, int length) {
    if (length == 1) {
        printf(" Getting current time\n");
    } else {
        printf(" Error: Wrong use of command. No argument nedded.\n");
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

