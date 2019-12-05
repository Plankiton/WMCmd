#include "menu.h"

static void appenditem(struct item *item, struct item **list, struct item **last){
    if (*last)
        (*last)->right = item;
    else
        *list = item;

    item->left = *last;
    item->right = NULL;
    *last = item;
}

