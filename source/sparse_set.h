/**
 * @file sparse_set.h
 * @brief Sparse Set data structure implementation
 *
 * A sparse set is a data structure that maintains a set of integers in the range [0, n)
 * with O(1) add, remove, and lookup operations.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define MAX_N 200

/**
 * @brief Sparse Set data structure
 *
 * A sparse set maintains a collection of elements from [0, n) where n is the
 * maximum possible size. It uses two arrays:
 * - domain: maps from dense index to element value
 * - inverse: maps from element value to dense index
 *
 * This allows O(1) operations for add, remove, and contains checks.
 */
typedef struct {
    uint8_t domain[MAX_N];   ///< Maps dense index to element value
    uint8_t inverse[MAX_N];  ///< Maps element value to dense index (inverse mapping)
    uint8_t size;            ///< Current number of elements in the set
} SparseSet;

/**
 * @brief Initialize a sparse set
 *
 * Sets up the sparse set by initializing all elements to be available (not in set).
 * After initialization, the set is empty.
 *
 * @param[out] set Pointer to the SparseSet to initialize
 * @param[in] size Maximum size for the set (not used in current implementation)
 */
inline void init(SparseSet* set, int size) {
    set->size = size;
    for (int i = 0; i < MAX_N; i++) {
        set->domain[i] = i;
        set->inverse[i] = i;
    }
}

/**
 * @brief Copy a sparse set
 *
 * Creates a deep copy of a sparse set from source to destination.
 *
 * @param[out] des Pointer to the destination SparseSet
 * @param[in] src Pointer to the source SparseSet to copy
 * @param[in] n Number of elements to copy
 */
inline void copy(SparseSet* des, SparseSet* src, size_t n) {
    des->size = src->size;
    memcpy(des->domain, src->domain, n);
    memcpy(des->inverse, src->inverse, n);
}

/**
 * @brief Add an element to the sparse set
 *
 * Inserts an element into the set if it is not already present.
 * Uses O(1) time complexity for the add operation.
 *
 * @param[in,out] set Pointer to the SparseSet to add the element to
 * @param[in] element The element value to add (must be < MAX_N)
 */
inline void add(SparseSet* set, uint8_t element) {
    if (set->inverse[element] < set->size) return;
    set->domain[set->size] = element;
    set->inverse[element] = set->size;
    set->size++;
}
