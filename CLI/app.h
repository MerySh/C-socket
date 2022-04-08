#define MAX_COMMANDS 3
#define MAX_SIZE 100

typedef struct Commands {
    const char *name;
    const char *info;
    void (*Command)(char **in);
} Commands_s;

void connect();
void disconnect();
void get_time();
