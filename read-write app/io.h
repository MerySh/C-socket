typedef struct {
    void (*write)(char *buff, int size);
    void (*read)();
} io_access_t;
