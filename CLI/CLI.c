#include <stdio.h>
#include <string.h>
#include "app.h"
#include "CLI.h"

void parse(char input[], char parsedInput[][MAX_SIZE]) {
    int j = 0, k = 0;
    for (int i = 0; i <= strlen(input); ++i) {
        if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n') {
            parsedInput[k][j] = '\0';
            ++k; j = 0;
        } else {
            parsedInput[k][j] = input[i];
            ++j;
        }
    }
}

void connectToCLI(Commands_s *commands, char *prompt) {
    while (1) {
        printf("%s", prompt);

        char input[MAX_SIZE];
        char parsedInput[MAX_SIZE][MAX_SIZE];
        fgets(input, MAX_SIZE, stdin);
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
                printf(" Error: command not found.\n");
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
}


