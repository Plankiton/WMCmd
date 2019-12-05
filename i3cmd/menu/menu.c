#include <stdlib.h>
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

Menu createMenu(int lenght){
    Menu menu;
    menu.lenght = 3;
    menu.selected = 0;

    return menu;
}

int main(int argc, char *argv[])
{
    Menu j = createMenu(3);
    printf("%i", j.lenght);

    return 0;
}
