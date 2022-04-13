typedef struct Commands {
    const char *name;
    const char *info;
    void (*Command)(char **in, int length);
} Commands_s;

void connecting();
void disconnecting();
void get_time();
void set_prompt();
