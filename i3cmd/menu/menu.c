#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "menu.h"

int main(int argc, char *argv[])
{
    Item *joao = (Item []){(Item){"joao", "maria"}, (Item){"j", "m"}};
    Menu j;

    j.submenus = (Menu []){{NULL}, {NULL}};
    j.submenus->items = joao;

    j.submenus->items = (Item []){(Item){"j", "k"}, (Item){"joao", "maria"}, (Item){"m", "o"}};

    for (int i = 0; i<3; i++)
        printf("%s: %s\n", j.submenus->items[i]);
    return 0;
}
