#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "CLI.h"

#define MAX_SIZE 100

/*
 * Parses user input onto string array that helps us to get inputed text by words
 */
void parse(char *input, char **parsed_input, int *count_parsed_input) 
{
    int j = 0;
    int c = *count_parsed_input;
    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n') {
            parsed_input[c][j] = '\0';
            ++c;
            j = 0;
        } else {
            parsed_input[c][j] = input[i];
            ++j;
        }
    }
    *count_parsed_input = c;
}

/*
 * Prints application's current prompt
 */
void print_prompt(char *prompt) {
    printf("%s ", prompt);
}

/*
 * Prints all commands and it's informations with nice style
 */
void print_all_commands(Commands_s *commands, int commands_count) {
    int max_size = 0; 
    for (int i = 0; i < commands_count; ++i) {
        if (strlen(commands[i].name) > max_size) {
            max_size = strlen(commands[i].name);
        }
    }
    for (int i = 0; i < commands_count; ++i) {
        int space = max_size - strlen(commands[i].name) + 1;
        printf(" %s %*c %s\n", commands[i].name, space, '|', commands[i].info); 
    }
}

/*
 * Checks if inputed text from user is an application's command or not returns 1 if it is and 0 if not a command
 */
int check_iscommand(Commands_s *commands, int commands_count, char **parsed_input, int *idx) {
    int flag = 0;
    for (int i = 0; i < commands_count; ++i) {
        if (!strcmp(parsed_input[0], commands[i].name)) {
            *idx = i;
            flag = 1;
            return flag;
         }
    }
    return flag;
}

/*
 * Runs CLI for current application, parses inputed text and checks
 * if it is a command then calls current command's function handler
 * if it is a <help> then prints all commands' information 
 * if it is command + <--help> then prints current command's information
 */
void run_cli(Commands_s *commands, int commands_count, char *input) {
    char **parsed_input = (char**)malloc(MAX_SIZE * sizeof(char*));
    for (int i = 0; i < MAX_SIZE; ++i) {
        parsed_input[i] = (char*)malloc(MAX_SIZE * sizeof(char));    
    }

    int count_parsed_input = 0;
    parse(input, parsed_input, &count_parsed_input);

    if (count_parsed_input >= 1) {
        int idx = 0;
        int is_command = check_iscommand(commands, commands_count, parsed_input, &idx);
        
        if (!is_command) { 
            if (!strcmp(parsed_input[0], "help") && count_parsed_input == 1) {
                print_all_commands(commands, commands_count);
            } else if (!strcmp(parsed_input[0], "help") && count_parsed_input != 1) {
                printf(" Error: Wrong use of command.\n");
            } else {
                printf(" Error: command not found.\n");
            }
        } else {
            if (!strcmp(parsed_input[1], "--help") && count_parsed_input == 2) { 
                printf(" %s\n", commands[idx].info);
            } else if (!strcmp(parsed_input[1], "--help") && count_parsed_input > 2) {
                printf(" Error: command not found.\n");
            } else {
                commands[idx].Command(parsed_input, count_parsed_input); 
            }
        }
    }
}


