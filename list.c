#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    if (lista == NULL) {
        return NULL;
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) 
{
    if(list->head == NULL)
    {
        return NULL;
    }
    list->current=list->head;
    return(list->current->data);
}

void * nextList(List * list) {
    if (list->current != NULL && list->current->next != NULL) 
    {
        list->current = list->current->next;
        return(list->current->data);
    }
    return NULL;
}

void * lastList(List * list) {
    Node* aux = list->head;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    list->current = aux;
    return(list->current->data);

    
}

void * prevList(List * list) {
    if(list->current == NULL || list->current->prev == NULL)
    {
        return NULL;
    }
    list->current = list->current->prev;
    return(list->current->data);
}

void pushFront(List * list, void * data) {
    Node * nuevoNodo = createNode(data);
    if(list->head == NULL)
    {
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
        list->current = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = list->head;
        list->head->prev = nuevoNodo;
        list->head = nuevoNodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* nuevoNodo = createNode(data);
    if(list->current->next == NULL)
    {
        list->current->next = nuevoNodo;
        nuevoNodo->prev = list->current;
        list->tail = nuevoNodo;
    }
    else{
        nuevoNodo->next = list->current->next;
        nuevoNodo->prev = list->current;
        list->current->next = nuevoNodo;
    }    
    
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void * dato = list->current->data;
    if(list->current->prev == NULL)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
        list->head = list->current;
        return dato;
    }
    if(list->current->next == NULL)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->tail = list->current;
        return(dato);
    }
    Node* aux = list->current->next;
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    list->current = aux;
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}