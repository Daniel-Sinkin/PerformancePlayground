#include "ppg_linked_list.h"

#include <limits.h>

void ppg_LinkedList_print(const ppg_LinkedList *head) {
    printf("[");
    while (head != NULL) {
        printf("%d", head->value);
        head = head->next;

        if (head != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

ppg_DynamicArray ppg_LinkedList_to_dynamic_array(const ppg_LinkedList *head) {
    ppg_DynamicArray arr;
    ppg_DynamicArray_initialize(&arr, 16);

    const ppg_LinkedList *curr = head;
    while (curr != NULL) {
        ppg_DynamicArray_push_back(&arr, curr->value);
        curr = curr->next;
    }

    return arr;
}

void ppg_LinkedList_initialize(ppg_LinkedList *list) {
    if (list != NULL) {
        return;
    }

    list->value = INT_MIN;
    list->next = NULL;
}

ppg_LinkedList *ppg_LinkedList_from_array(const int array[], size_t array_size) {
    if (array_size == 0) {
        return NULL;
    }

    ppg_LinkedList *head = malloc(sizeof(ppg_LinkedList));
    if (head == NULL) PANIC_MALLOC();

    ppg_LinkedList_initialize(head);
    head->value = array[0];

    ppg_LinkedList *curr = head;
    for (size_t i = 1; i < array_size; i++) {
        ppg_LinkedList *new_node = malloc(sizeof(ppg_LinkedList));

        if (new_node == NULL) PANIC_MALLOC();

        ppg_LinkedList_initialize(new_node);
        new_node->value = array[i];

        curr->next = new_node;
        curr = new_node;
    }

    return head;
}