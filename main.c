#include <ppg_cache_hierarchy.h>
#include <ppg_dynamic_array.h>
#include <ppg_linked_list.h>
#include <ppg_util.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    ppg_LinkedList header = {0, NULL};
    ppg_LinkedList second = {1, NULL};
    header.next = &second;
    ppg_LinkedList third = {2, NULL};
    second.next = &third;

    ppg_LinkedList_print(&header);

    printf("\n");

    ppg_DynamicArray arr = ppg_LinkedList_to_dynamic_array(&header);

    ppg_DynamicArray_print(&arr);

    ppg_DynamicArray_free(&arr);

    printf("\n");

    int x[5] = {1, 2, 3, 4, 5};

    ppg_LinkedList from_array = ppg_LinkedList_from_array(x, 5);

    ppg_LinkedList_print(&from_array);

    return 0;
}