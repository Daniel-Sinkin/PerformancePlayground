#pragma once

#include "ppg_dynamic_array.h"

typedef struct ppg_LinkedList ppg_LinkedList;

struct ppg_LinkedList {
    int value;
    ppg_LinkedList *next;
};

ppg_DynamicArray ppg_LinkedList_to_dynamic_array(const ppg_LinkedList *head);
ppg_LinkedList ppg_LinkedList_from_array(const int array[], size_t array_size);

void ppg_LinkedList_print(const ppg_LinkedList *head);
void ppg_LinkedList_initialize(ppg_LinkedList *list);
