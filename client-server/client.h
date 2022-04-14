/*
 * structure of application's commands, which contains
 * command name, info aboit it and function handler
 */
typedef struct Commands {
    const char *name;
    const char *info;
    void (*Command)(char **in, int length);
} Commands_s;

/*
 * Brief: function handlers 
 *
 * connecting: for connecting to a server
 * disconnecting: for disconnecting from the server
 * get_time: for getting server's current time
 * set_prompt: for changing current prompt
 */
void connecting();
void disconnecting();
void get_time();
void set_prompt();
