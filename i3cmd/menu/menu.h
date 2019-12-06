typedef struct __item {
    char * value, * output;
} Item;

typedef union __menu {
    Item * items;
    union __menu * submenus;
} Menu;
