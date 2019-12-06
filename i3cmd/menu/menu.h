typedef struct __item {
    char * value, * output;
} Item;

typedef union __menu {
    Item * items;
    union __menu * submenus;
} Menu;

typedef struct {
    int __a;
    int __b;
    int __c;
} TEST;

TEST ITEM_NULL = {0, 0, 0};

int TEST_ISEQUAL(TEST a, TEST b){
    if (a.__a == b.__a){
        if (a.__b == b.__b){
            if(a.__c == b.__c){
                return 1;
            }else return 0;
        }else return 0;
    }else return 0;
}
