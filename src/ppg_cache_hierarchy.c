#include <ppg_cache_hierarchy.h>
#include <ppg_util.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <sysinfoapi.h>
#include <windows.h>
#elif __APPLE__
#include <sys/sysctl.h>
#elif __linux__
#include <unistd.h>
#endif

double ppg_cache_hierarchy_sum_chunks(double *data, size_t data_size, size_t chunk_size) {
    double result = 0.0;
    for (size_t i = 0; i < data_size; i += chunk_size) {
        for (size_t j = i; j < i + chunk_size && j < data_size; j++) {
            result += data[j];
        }
    }
    return result;
}

double ppg_cache_hierarchy_benchmark_sum_chunks(double *data, size_t data_size, size_t chunk_size) {
    clock_t start = clock();
    ppg_cache_hierarchy_sum_chunks(data, data_size, chunk_size);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to get cache sizes
cache_history_CacheDataInfo cache_hierarchy_get_cache_data_info() {
    cache_history_CacheDataInfo cache_info = {0, 0}; // Initialize to 0

#ifdef _WIN32
    // Use Windows API to retrieve cache sizes
    DWORD buffer_size = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = NULL;

    // Get the size of the buffer
    GetLogicalProcessorInformation(NULL, &buffer_size);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
    if (!buffer) {
        perror("Memory allocation failed");
        return cache_info;
    }

    // Retrieve processor information
    if (GetLogicalProcessorInformation(buffer, &buffer_size)) {
        for (size_t i = 0; i < buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++) {
            if (buffer[i].Relationship == RelationCache) {
                CACHE_DESCRIPTOR cache = buffer[i].Cache;
                if (cache.Level == 1 && cache.Type == CacheData) {
                    cache_info.l1_data_cache_size = cache.Size;
                } else if (cache.Level == 2) {
                    cache_info.l2_cache_size = cache.Size;
                }
            }
        }
    }
    free(buffer);

#elif __APPLE__
    // Use sysctl for macOS
    size_t size = sizeof(size_t);

    // Get L1 data cache size
    if (sysctlbyname("hw.l1dcachesize", &cache_info.l1_data_cache_size, &size, NULL, 0) != 0) {
        perror("Failed to retrieve L1 data cache size");
    }

    // Get L2 cache size
    if (sysctlbyname("hw.l2cachesize", &cache_info.l2_cache_size, &size, NULL, 0) != 0) {
        perror("Failed to retrieve L2 cache size");
    }

#elif __linux__
    // Use sysfs on Linux
    FILE *file = fopen("/sys/devices/system/cpu/cpu0/cache/index0/size", "r");
    if (file) {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), file)) {
            cache_info.l1_data_cache_size = atoi(buffer) * 1024; // Convert KB to bytes
        }
        fclose(file);
    }

    file = fopen("/sys/devices/system/cpu/cpu0/cache/index2/size", "r");
    if (file) {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), file)) {
            cache_info.l2_cache_size = atoi(buffer) * 1024; // Convert KB to bytes
        }
        fclose(file);
    }
#endif

    return cache_info;
}

void ppg_cache_hierarchy_print_latency_comparison() {
    cache_history_CacheDataInfo cache_info = cache_hierarchy_get_cache_data_info();
    size_t l1_data_cache_size = cache_info.l1_data_cache_size;
    size_t l2_cache_size = cache_info.l2_cache_size;

    printf("L1 Data Cache Size: %zu bytes\n", l1_data_cache_size);
    printf("L2 Cache Size: %zu bytes\n", l2_cache_size);

    size_t data_size_l1 = l1_data_cache_size / sizeof(double);
    size_t data_size_l2 = l2_cache_size / sizeof(double);

    srand((unsigned)time(NULL));

    double *data_l1 = ppg_util_generate_random_data(data_size_l1);
    double *data_l2 = ppg_util_generate_random_data(data_size_l2);

    size_t chunk_sizes[] = {1, 2, 4, 8, 16};
    double times_l1[5], times_l2[5];

    printf("\nBenchmarking L1-sized data...\n");
    for (int i = 0; i < 5; i++) {
        times_l1[i] = ppg_cache_hierarchy_benchmark_sum_chunks(data_l1, data_size_l1, chunk_sizes[i]);
        printf("Chunk size %zu: %.6f ms\n", chunk_sizes[i], times_l1[i]);
    }

    printf("\nBenchmarking L2-sized data...\n");
    for (int i = 0; i < 5; i++) {
        times_l2[i] = ppg_cache_hierarchy_benchmark_sum_chunks(data_l2, data_size_l2, chunk_sizes[i]);
        printf("Chunk size %zu: %.6f ms\n", chunk_sizes[i], times_l2[i]);
    }

    printf("\nSpeedup Comparisons:\n");
    for (int i = 0; i < 5; i++) {
        printf("L1 (chunk %zu) is %.2fx faster than L2 (chunk %zu)\n",
            chunk_sizes[i], times_l2[i] / times_l1[i], chunk_sizes[i]);
    }
    for (int i = 1; i < 5; i++) {
        printf("L1 (chunk %zu) is %.2fx faster than L1 (chunk 1)\n",
            chunk_sizes[i], times_l1[0] / times_l1[i]);
    }

    free(data_l1);
    free(data_l2);
}