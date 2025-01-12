#pragma once

#include <ppg_util.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *start;
    int *end;
    int *capacity;
} ppg_DynamicArray;

void ppg_DynamicArray_initialize(ppg_DynamicArray *dynamic_array, size_t initial_capacity);

void ppg_DynamicArray_free(ppg_DynamicArray *dynamic_array);

void ppg_DynamicArray_push_back(ppg_DynamicArray *dynamic_array, int value);

int ppg_DynamicArray_at(const ppg_DynamicArray *dynamic_array, size_t idx);

void ppg_DynamicArray_print(const ppg_DynamicArray *dynamic_array);

FORCE_INLINE
size_t ppg_DynamicArray_size(const ppg_DynamicArray *dynamic_array) {
    return dynamic_array->end - dynamic_array->start;
}

FORCE_INLINE
size_t ppg_DynamicArray_capacity(const ppg_DynamicArray *dynamic_array) {
    return dynamic_array->capacity - dynamic_array->start;
}

void ppg_dynamic_array_example_1();
/*
Size: 0
Capacity: 4
Values = []

Size: 1
Capacity: 4
Values = [10.00]

Size: 2
Capacity: 4
Values = [10.00, 20.00]

Size: 3
Capacity: 4
Values = [10.00, 20.00, 30.00]

Size: 4
Capacity: 4
Values = [10.00, 20.00, 30.00, 40.00]

Size: 5
Capacity: 8
Values = [10.00, 20.00, 30.00, 40.00, 50.00]

Size: 6
Capacity: 8
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00]

Size: 7
Capacity: 8
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00]

Size: 8
Capacity: 8
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00]

Size: 9
Capacity: 16
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00]

Size: 10
Capacity: 16
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00, 100.00]

Size: 11
Capacity: 16
Values = [10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00, 100.00, 110.00]
*/