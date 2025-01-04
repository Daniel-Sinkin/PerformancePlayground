#include <ppg_util.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double *ppg_util_generate_random_data(size_t size) {
    double *data = (double *)malloc(size * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; i++) {
        data[i] = (double)rand() / RAND_MAX;
    }
    return data;
}
