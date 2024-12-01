#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define MAX_N 200

typedef struct {
    uint8_t domain[MAX_N];
    uint8_t inverse[MAX_N];
    uint8_t size;
} SparseSet;

inline void init(SparseSet *set, int size) {
    set->size = size;
    for (int i = 0; i < MAX_N; i++) {
        set->domain[i] = i;
        set->inverse[i] = i;
    }
}

inline void copy(SparseSet *des, SparseSet *src, size_t n) {
    des->size = src->size;
    memcpy(des->domain, src->domain, n);
    memcpy(des->inverse, src->inverse, n);
}

inline void add(SparseSet *set, uint8_t element) {
    if (set->inverse[element] < set->size) return;
    set->domain[set->size] = element;
    set->inverse[element] = set->size;
    set->size++;
}
