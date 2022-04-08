#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "app.h"
#include "CLI.h"

void parse(char *input, char **parsedInput) {
    int j = 0, k = 0;
    for (int i = 0; i <= length; ++i) {
        if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n') {
            parsedInput[k][j] = '\0';
            ++k; j = 0;
        } else {
            parsedInput[k][j] = input[i];
            ++j;
        }
    }
}

void printPrompt(char *prompt) {
    printf("%s", prompt);
}

void runCLI(Commands_s *commands, char *input) {
        char **parsedInput = (char**)malloc(MAX_SIZE * sizeof(*parsedInput));
        parse(input, parsedInput);

        char command[MAX_SIZE];
        int flag = 0;
        int idx;
        if (strlen(parsedInput[0]) > 1) {
            for (int i = 0; i < MAX_COMMANDS; ++i) {
                if (!strcmp(parsedInput[0], commands[i].name)) {
                    strcpy(command, parsedInput[0]);
                    idx = i;
                    flag = 1;
                    break;
                }
            }

            if (!flag) { 
                if (!strcmp(parsedInput[0], "help")) {
                    if (!strlen(parsedInput[1])) {
                        for (int i = 0; i < MAX_COMMANDS; ++i) {
                            printf(" %s | %s\n", commands[i].name, commands[i].info); 
                        }
                    } else {
                        printf(" Error: Wrong use of command.\n");
                    }
                } else {
                    printf(" Error: command not found.\n");
                }
            } else {
                if (!strcmp(parsedInput[1], "--help")) { 
                    if (!strlen(parsedInput[2])) {
                        printf(" %s\n", commands[idx].info);
                    } else {
                        printf(" Error: command not found.\n");
                    }
                } else {
                    commands[idx].Command(parsedInput); 
               }
            }
        }
}


