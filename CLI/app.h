#define MAX_COMMANDS 4
#define MAX_SIZE 100

typedef struct Commands {
    const char *name;
    const char *info;
    void (*Command)(char in[MAX_SIZE][MAX_SIZE]);
} Commands_s;

void help();
void connect();
void disconnect();
void get_time();
