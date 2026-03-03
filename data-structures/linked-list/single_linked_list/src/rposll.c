#include "rposll.h"
#include <stdlib.h>

// -- List Life Cycle -- 
sll *sll_create(void) {
    sll *new_sll = malloc(sizeof(sll));
    if (!new_sll) return NULL;

    new_sll->size = 0;
    return new_sll;
}


void sll_destroy(sll *list, void (*free_fn)(void *)) {
    sll_node *current_node = list->head;

    while (current_node != NULL) {
        sll_node *next_node = current_node->next;

        if (free_fn != NULL) {
            free_fn(current_node->data);
        }

        free(current_node);
        current_node = next_node;
    }

    list->head = NULL;
    list->size = 0;
}


sll_node *create_node(void *data) {
    sll_node *new_node = malloc(sizeof(sll_node));
    if (!new_node) return NULL;

    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int insert_at_head(sll *list, void *data) {
    sll_node *node;

    if (!list) return -1;

    node = create_node(data);
    if (!node) return -1;


    if (list->size == 0) { 
        list->tail = node;
    }

    node->next = list->head;
    list->head = node;
    list->size++;

    return 0;

}
