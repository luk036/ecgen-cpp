/*
 * Copyright (c) 2019 Joe Sawada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define MAX_N 70

#define MIN(a, b) ((a) <= (b)) ? (a) : (b)

//-------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------
int N, D;
int a[MAX], b[MAX];
int THRESHOLD;
int D_MINUS_1;
int D_TIMES_D_MINUS_1;
int N_MINUS_D;
int N1;
int N2;
size_t SIZE_N;

typedef struct {
    uint8_t domain[MAX_N];
    uint8_t inverse[MAX_N];
    int size;
} SparseSet;

void init(SparseSet *set, int size) {
    set->size = size;
    for (int i = 0; i < MAX_N; i++) {
        set->domain[i] = i;
        set->inverse[i] = i;
    }
}

void copy(SparseSet *des, SparseSet *src, size_t n) {
    des->size = src->size;
    memcpy(des->domain, src->domain, n);
    memcpy(des->inverse, src->inverse, n);
}

void add(SparseSet *set, int element) {
    int loc = set->inverse[element];
    if (loc < set->size)
        return;
    int elem = set->domain[set->size];
    set->domain[loc] = elem;
    set->domain[set->size] = element;
    set->inverse[element] = set->size;
    set->inverse[elem] = loc;

    set->size++;
}

//-------------------------------------------------------------
void PrintD() {
    // print a
    for (int i = 1; i <= D; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    exit(0);
}

/*-----------------------------------------------------------*/
// FIXED DENSITY
/*-----------------------------------------------------------*/
void GenD(int t, int p, int tt, SparseSet *diffset) {
    SparseSet differences;
    // copy(&differences, diffset, SIZE_N);
    differences.size = diffset->size;
    memcpy(differences.domain, diffset->domain, SIZE_N);
    memcpy(differences.inverse, diffset->inverse, SIZE_N);

    for (int i = 0; i < t; i++) {
        int diff = a[t] - a[i];
        int element = MIN(diff, N - diff);
        int loc = differences.inverse[element];
        if (loc < differences.size)
            continue;
        int elem = differences.domain[differences.size];
        differences.domain[loc] = elem;
        differences.domain[differences.size] = element;
        differences.inverse[element] = differences.size;
        differences.inverse[elem] = loc;
        differences.size++;
        // add(&differences, MIN(diff, N - diff));
    }

    if (t >= THRESHOLD) {
        if (differences.size < N1 + tt) {
            return;
        }
    }

    int t1 = t + 1;
    if (t1 >= D)
        PrintD();
    else {
        int tail = N_MINUS_D + t1;
        int max = a[t1 - p] + a[p];
        int tt1 = t1 * (t1 + 1) / 2;
        if (max <= tail) {
            a[t1] = max;
            b[t1] = b[t1 - p];

            GenD(t1, p, tt1, &differences);
            if (b[t1] == 0) {
                b[t1] = 1;
                GenD(t1, t1, tt1, &differences);
            }
            tail = max - 1;
        }
        for (int j = tail; j >= a[t] + 1; j--) {
            a[t1] = j;
            b[t1] = 1;
            GenD(t1, t1, tt1, &differences);
        }
    }
}

/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
void Init() {
    int j;

    for (j = 0; j <= D; j++)
        a[j] = 0;
    a[D] = N;
    a[0] = 0; // for convenience

    D_MINUS_1 = D - 1;
    D_TIMES_D_MINUS_1 = D * (D - 1);
    N_MINUS_D = N - D;
    N2 = N / 2;
    N1 = N2 - D_TIMES_D_MINUS_1 / 2;
    SIZE_N = (N2 + 1) * sizeof(uint8_t);

    SparseSet differences;
    init(&differences, 0);

    for (j = N - D + 1; j >= (N - 1) / D + 1; j--) {
        a[1] = j;
        b[1] = 1;
        GenD(1, 1, 1, &differences);
    }
    printf("No solution is found.\n");
}

//------------------------------------------------------
void usage() { printf("Usage: necklace [n] [density] [threshold]\n"); }
//--------------------------------------------------------------------------------
int main(int argc, char **argv) {
    if (argc < 4) {
        usage();
        return 1;
    }
    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%d", &D);
    sscanf(argv[3], "%d", &THRESHOLD);

    if (N > D * (D - 1) + 1) {
        printf("Error: N must be less than D*(D-1)+1\n");
        return 1;
    }

    Init();
    return 0;
}
