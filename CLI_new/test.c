#include <stdio.h>

typedef struct COmmands {
    const char *name;
    const char *info;
    void (*Command)(char **, int);
} Commands_s;

Commands_s commands[] = {
    {"a", "B"},
    {"a", "B"},
    {"a", "B"},
    {"a", "B"}
};

int main() {
    printf("%ld", sizeof(commands));
}
