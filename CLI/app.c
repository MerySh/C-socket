#include <stdio.h>
#include <string.h>
#include "app.h"
#include "CLI.h"

Commands_s commands[] = {
    { "help", "Command gives all commands", &help },
    { "connect", "Command is for connecting", &connect },
    { "disconnect", "Command is for disconnecting", &disconnect },
    { "get_time", "Command gives current time", &get_time }
};

void help() {
    for (int i = 0; i < MAX_COMMANDS; ++i) {
        printf(" %s | %s\n", commands[i].name, commands[i].info);
    }
}

void connect(char in[MAX_SIZE][MAX_SIZE]) {
    if (strlen(in[1]) && strlen(in[2])) {
        printf(" Connecting to port: %s, ip_address: %s\n", in[2], in[1]); 
    } else {
        printf(" Error: No port or ip_address was given.\n");
    }
}

void disconnect(char in[MAX_SIZE][MAX_SIZE]) {
    if (!strlen(in[1])) {
        printf(" Disconenct\n");    
    } else {
        printf(" Error: Wrong use of command.\n");
    }
}

void get_time(char in[MAX_SIZE][MAX_SIZE]) {
    if (!strlen(in[1])) {
        printf(" Getting current time\n");
    } else {
        printf(" Error: Wrong use of command.\n");
    }
}

int main() {
    char *prompt = "> ";

    connectToCLI(commands, prompt);
}

