/*
 * brief: runs CLI for current application
 *
 * commands: array of all application commands
 * commands_count: number of commands
 * input: inputed text from user
 *
 * returns: nothing
 */
void run_cli(Commands_s *commands, int commands_count, char *input);

/*
 * brief: parses inputed string from user
 *
 * input: inputed text from user
 * parsed_input: parsed text from CLI
 * 
 * returns: nothing
 */
void parse(char *input, char **parsed_input, int *count_parsed_input);

/*
 * brief: prints application's prompt
 *
 * prompt: application's prompt
 * 
 * returns: nothing
 */
void print_prompt(char *prompt);

/*
 * brief: prints application's all command's name and info
 *
 * commands: array of all application commands
 * commands_count: number of commands
 * 
 * returns: nothing
 */
void print_all_commands(Commands_s *commands, int commands_count);

/*
 * brief: checks if there is such a command or not
 *
 * commands: array of all application commands
 * commands_count: number of commands
 * parsed_input: parsed text from CLI
 * idx: current index
 * 
 * returns: true or false 1/0
 */
int check_iscommand(Commands_s *commands, int commands_count, char **parsed_input, int *idx);
