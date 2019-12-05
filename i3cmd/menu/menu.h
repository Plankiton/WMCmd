struct item {
    char *text;
    struct item *left, *right;
    int out;
};


static void appenditem(struct item *item, struct item **list, struct item **last);
