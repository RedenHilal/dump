#ifndef LIST_H
#define LIST_H

enum{
    INSERT_AFTER,
    INSERT_BEFORE
};

typedef  struct listElement {
    int key;
    void * data;
    struct listElement * next;
}listElement;

typedef struct {
    int size;
    listElement *head;
    listElement *tail;
}linkedList;



void init(linkedList*);


int insertAwal(linkedList*,void*,int*);


int insertAkhir(linkedList*,void*,int*);


int insertAfter(linkedList*,void*,int*,int);


int insertBefore(linkedList*,void*,int*,int);


listElement*searchElement(linkedList*,int,int);


void printMenu();


int targetInput();


int takeInput(linkedList*,char,int*);

void printList(linkedList*);



#endif
