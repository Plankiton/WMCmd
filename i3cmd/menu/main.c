#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

int main(int argc, char *argv[])
{
    Menu j;

    j.submenus = (Menu []){{NULL}, {NULL}};
    j.submenus->items = (Item []){
            (Item){"j", "k"},
            (Item){"joao", "maria"},
            (Item){"m", "o"},
            (Item){NULL, NULL}
    };
    j.submenus[1].submenus = (Menu []){{NULL}};
    j.submenus[1].submenus->title = "maria";
    j.submenus[1].submenus->items = (Item []){
        (Item){"sub", "menu"},
        (Item){NULL, NULL}
    };

    for (int i = 0; !is_null(j.submenus->items[i]); i++)
        printf("%s\n", j.submenus->items[i].value);
    for (int i = 0; !is_null(j.submenus[1].submenus->items[i]); i++){
        printf("%s:\n", j.submenus[1].submenus->title);
        printf("\t%s\n", j.submenus[1].submenus->items[i].value);
    }
    return 0;
}
