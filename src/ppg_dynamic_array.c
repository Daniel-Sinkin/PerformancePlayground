#include <ppg_dynamic_array.h>

#include <ppg_util.h>

#include <stdio.h>
#include <stdlib.h>

void ppg_DynamicArray_initialize(ppg_DynamicArray *dynamic_array, size_t initial_capacity) {
    double *malloc_ptr = malloc(0);
    dynamic_array->start = malloc(initial_capacity * sizeof(double));
    if (!dynamic_array->start) {
        fprintf(stderr, "Failed to allocate memory!");
        abort();
    }
    dynamic_array->end = dynamic_array->start;
    dynamic_array->capacity = dynamic_array->start + initial_capacity;
}

void ppg_DynamicArray_free(ppg_DynamicArray *dynamic_array) {
    free(dynamic_array->start);
    dynamic_array->start = NULL;
    dynamic_array->end = NULL;
    dynamic_array->capacity = NULL;
}

void ppg_DynamicArray_push_back(ppg_DynamicArray *dynamic_array, double value) {
    if (dynamic_array->end == dynamic_array->capacity) {
        size_t current_size = dynamic_array->capacity - dynamic_array->start;
        size_t new_size;
        if (current_size == 0) {
            new_size = 1;
        } else {
            new_size = 2 * current_size;
        }
        dynamic_array->start = realloc(dynamic_array->start, new_size * sizeof(double));
        if (!dynamic_array->start) {
            fprintf(stderr, "Failed to allocate memory during append!\n");
            abort();
        }

        dynamic_array->capacity = dynamic_array->start + new_size;
        dynamic_array->end = dynamic_array->start + current_size;
    }

    *(dynamic_array->end) = value;
    dynamic_array->end++;
}

double ppg_DynamicArray_at(const ppg_DynamicArray *dynamic_array, size_t idx) {
    if (idx < ppg_DynamicArray_size(dynamic_array)) {
        return *(dynamic_array->start + idx);
    } else {
        fprintf(stderr, "Out of bounds access on ppg_DynamicArray_at");
        abort();
    }
}

void ppg_DynamicArray_print(const ppg_DynamicArray *dynamic_array) {
    printf("[");
    size_t n = ppg_DynamicArray_size(dynamic_array);
    for (size_t i = 0; i < n; i++) {
        printf("%.2f", ppg_DynamicArray_at(dynamic_array, i));
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void ppg_dynamic_array_example_1() {
    ppg_DynamicArray array;
    ppg_DynamicArray_initialize(&array, 4);

    for (size_t i = 0; i < 12; i++) {
        printf("Size: %zu\n", ppg_DynamicArray_size(&array));
        printf("Capacity: %zu\n", ppg_DynamicArray_capacity(&array));
        printf("Values = ");
        ppg_DynamicArray_print(&array);
        printf("\n");

        ppg_DynamicArray_push_back(&array, (double)(10.0 * (i + 1)));
    }

    ppg_DynamicArray_free(&array);
}