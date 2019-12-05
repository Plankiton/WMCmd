typedef struct __item {
    char * value, * output;
} Item;

typedef union __menu {
    Item * items;
    union __menu * submenu;
} _menu;

typedef struct {
    int lenght, selected;
    _menu menu;
} Menu;
