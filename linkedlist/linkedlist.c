#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "list.h"

int main(){
    initscr();
    
    int key = 0,running = 1;
    char input;
    linkedList list;
    init(&list);

    while(running){
        printMenu();
        scanf("%c",&input);

        if(input == 0) {
            running = 0;
            continue;
        }
        takeInput(&list, input, &key);
    }
    endwin();

}

