#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "list.h"

#include "list.h"

void init(linkedList * list){
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

int insertAwal(linkedList*list,void*data,int *key){
    listElement * temp = malloc(sizeof(listElement));
    if (temp == NULL)
        return 1;

    temp->key = (*key)++;
    temp->next = list->head;
    list->head = temp;

    if (list->size == 0)
        list->tail = temp;

    list->size +=1;
    return 0;
}

int insertAkhir(linkedList *list,void*data,int*key){
    listElement * temp = malloc(sizeof(listElement));
    if (temp == NULL)
        return 1;

    temp->key = (*key)++;
    temp->next = NULL;

    if (list->size == 0){
        list->tail = temp;
        list->head = temp;
        list->size +=1;
        return 0;
    }

    list->tail->next = temp;
    list->tail = temp;

    list->size+=1;
    return 0;
}

int insertAfter(linkedList *list,void*data,int*key, int target){
    listElement *iterator = searchElement(list, target,INSERT_AFTER);

    if (iterator==NULL)
        return -1;

    if (iterator == list->tail){
        return insertAkhir(list, data, key);
    }

    listElement *temp = malloc(sizeof(listElement));
    if (temp == NULL)
        return 1;

    temp->key = (*key)++;
    temp->next = iterator->next;
    iterator->next = temp;

    list->size++;
    return 0;
}

int insertBefore(linkedList *list,void*data,int*key,int target){
    if (list->head == NULL)
        return -1;

    if(list->head->key == target){
        return insertAwal(list, data,key);
    }

    listElement * iterator = searchElement(list, target,INSERT_BEFORE);

    if (iterator == NULL)
        return -1;

    listElement * temp = malloc(sizeof(listElement));
    if (temp == NULL)
        return 1;

    temp->key = (*key)++;
    temp->next = iterator->next;
    iterator->next = temp;

    list->size++;
    return 0;
}

listElement * searchElement (linkedList *list,int target,int mode ){
    listElement * retValue=NULL;
    switch (mode) {
        case INSERT_AFTER:
            for (listElement *iterator = list->head; iterator!=NULL; iterator = iterator->next) {
                if (iterator->key == target)
                    return iterator;
            }
            break;
        case INSERT_BEFORE:
            if(list->head==NULL) return NULL;
            for (listElement * iterator = list->head->next;iterator!=NULL;iterator = iterator->next){
                if(iterator->key == target)
                    return retValue;
                retValue = iterator;
            }
            break;
    }
    return NULL;
}

void printMenu(){
    int input;
    system("clear");
    printw("Menu:\n0 - Exit\n1 - Insert Awal\n2 - Insert Akhir\n3 - Insert After\n4 - Insert Before\n5 - Display List\n\n");
    move(5, 1);
    input = getch();
}

int targetInput(){
    int dummy;
    printf("Masukkan Key yang dimiliki ListElement: ");
    scanf("%d",&dummy);
    getchar();
    return dummy;
}

int takeInput(linkedList *list, char input,int*key){
    int length,status,target;
    char * data;

    if(input < 5){
        printf("Length of data: ");
        scanf("%d",&length);
        getchar();
        
        if((data=malloc(length))==NULL) return 1;
        printf("Input Your Data: \n");
        fgets(data,length, stdin);
        data[strcspn(data, "\n")] = 0;
    }

    switch (input) {
        case 1:
            return insertAwal(list,data,key);
        case 2:
            return insertAkhir(list,data,key);
        case 3:
            target = targetInput();
            return insertAfter(list,data,key,target);
        case 4:
            target = targetInput();
            return insertBefore(list,data,key,target);
        case 5:
            printList(list);
            return 0;
        default:
            printf("Invalid Option\n");
            return 2;
    }
}

void printList(linkedList*list){
    for(listElement*start = list->head;start!=NULL;start = start->next){
        printf("Key: %d\nData: %s\n\n", start->key,(char*)start->data);
    }
}