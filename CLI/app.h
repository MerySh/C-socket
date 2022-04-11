#define MAX_COMMANDS 4
#define MAX_SIZE 100

typedef struct Commands {
    const char *name;
    const char *info;
    void (*Command)(char **in, int length);
} Commands_s;

char prompt_[MAX_SIZE];

void connect();
void disconnect();
void get_time();
void prompt();
