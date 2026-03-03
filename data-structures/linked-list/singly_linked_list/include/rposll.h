#ifndef RPOSLL_H
#define RPOSLL_H

#include <unistd.h> // size_t


typedef struct sll_node {
    void *data;
    struct sll_node *next;
} sll_node;


typedef struct sll {
    struct sll_node *head;
    struct sll_node *tail;
    size_t size;
} sll;

// -- List LIfe Cycle --
sll *sll_create(void);
void sll_destroy(sll *list, void (*free_fn)(void *));


// -- Nodes -- 
sll_node *create_node(void *data);

// -- Insertions --
void insert_at_head(sll *list, void *data);

#endif