typedef struct __item {
    char * value, * output;
} Item;

typedef struct __menu {
    char * title;
    Item * items;
    struct __menu * submenus;
} Menu;

#define is_null(item) (item.value == NULL && item.output == NULL)
