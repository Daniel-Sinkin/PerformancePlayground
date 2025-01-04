#pragma once

#include <stdio.h>

typedef struct {
    size_t l1_data_cache_size;
    size_t l2_cache_size;
} cache_history_CacheDataInfo;

cache_history_CacheDataInfo cache_hierarchy_get_cache_data_info();
double ppg_cache_hierarchy_benchmark_sum_chunks(double *data, size_t data_size, size_t chunk_size);
void ppg_cache_hierarchy_print_latency_comparison();
/*
L1 Data Cache Size: 65536 bytes
L2 Cache Size: 4194304 bytes

Benchmarking L1-sized data...
Chunk size 1: 0.000067 ms
Chunk size 2: 0.000050 ms
Chunk size 4: 0.000052 ms
Chunk size 8: 0.000051 ms
Chunk size 16: 0.000050 ms

Benchmarking L2-sized data...
Chunk size 1: 0.004140 ms
Chunk size 2: 0.003171 ms
Chunk size 4: 0.002877 ms
Chunk size 8: 0.002896 ms
Chunk size 16: 0.002803 ms

Speedup Comparisons:
L1 (chunk 1) is 61.79x faster than L2 (chunk 1)
L1 (chunk 2) is 63.42x faster than L2 (chunk 2)
L1 (chunk 4) is 55.33x faster than L2 (chunk 4)
L1 (chunk 8) is 56.78x faster than L2 (chunk 8)
L1 (chunk 16) is 56.06x faster than L2 (chunk 16)
L1 (chunk 2) is 1.34x faster than L1 (chunk 1)
L1 (chunk 4) is 1.29x faster than L1 (chunk 1)
L1 (chunk 8) is 1.31x faster than L1 (chunk 1)
L1 (chunk 16) is 1.34x faster than L1 (chunk 1)
*/
