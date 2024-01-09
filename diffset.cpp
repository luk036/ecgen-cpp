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
typedef struct {
    int n;
    int d;
    int a[MAX];
    int b[MAX];
    int threshold;
    int d_minus_1;
    int d_times_d_minus_1;
    int n_minus_d;
    int n1;
    int n2;
    size_t size_n;
} DiffCover;

//-------------------------------------------------------------
/**
 * Prints the generated set to stdout and exits.
 */
void PrintD(const DiffCover *diff_cover) {
    // print a
    for (int i = 1; i <= diff_cover->d; i++) {
        printf("%d ", diff_cover->a[i]);
    }
    printf("\n");
    exit(0);
}

/*-----------------------------------------------------------*/
// FIXED DENSITY
/*-----------------------------------------------------------*/
/**
 * Recursively generates all possible D-sets by building them up one
 * element at a time.
 *
 * t - Current element index being added
 * p - Previous element index
 * tt - Triangle number of current index t
 * diffset[] - Bit array tracking differences between elements
 */
void GenD(DiffCover *diff_cover, int t, int p, int tt, int8_t diffset[]) {
    int8_t differences[MAX_N];
    memcpy(differences, diffset, diff_cover->size_n);

    for (int i = 0; i < t; i++) {
        int diff = diff_cover->a[t] - diff_cover->a[i];
        differences[MIN(diff, diff_cover->n - diff)] = 1;
    }
    if (t >= diff_cover->threshold) {
        int count = 0;
        for (int i = 1; i <= diff_cover->n2; i++) {
            if (differences[i] != 0) {
                count++;
            }
        }
        if (count < diff_cover->n1 + tt) {
            return;
        }
    }

    int t1 = t + 1;
    if (t1 >= diff_cover->d)
        PrintD(diff_cover);
    else {
        int tail = diff_cover->n_minus_d + t1;
        int max = diff_cover->a[t1 - p] + diff_cover->a[p];
        int tt1 = t1 * (t1 + 1) / 2;
        if (max <= tail) {
            diff_cover->a[t1] = max;
            diff_cover->b[t1] = diff_cover->b[t1 - p];

            GenD(diff_cover, t1, p, tt1, differences);
            if (diff_cover->b[t1] == 0) {
                diff_cover->b[t1] = 1;
                GenD(diff_cover, t1, t1, tt1, differences);
            }
            tail = max - 1;
        }
        for (int j = tail; j >= diff_cover->a[t] + 1; j--) {
            diff_cover->a[t1] = j;
            diff_cover->b[t1] = 1;
            GenD(diff_cover, t1, t1, tt1, differences);
        }
    }
}

/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/**
 * Initializes global variables and arrays used for generating necklaces.
 * Sets up the 'a' and 'b' arrays to track candidate necklaces,
 * the 'differences' array to track differences between necklace elements,
 * and key constants used in the generation algorithms.
 * Calls GenD() recursively to generate all possible necklaces.
 */
void Init(DiffCover *diff_cover) {
    int8_t differences[MAX_N];
    memset(differences, 0, diff_cover->size_n);
    differences[0] = 1;

    for (int j = diff_cover->n_minus_d + 1;
         j >= (diff_cover->n - 1) / diff_cover->d + 1; j--) {
        diff_cover->a[1] = j;
        diff_cover->b[1] = 1;
        GenD(diff_cover, 1, 1, 1, differences);
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
    int n, d, threshold;

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &d);
    sscanf(argv[3], "%d", &threshold);

    if (n > d * (d - 1) + 1) {
        printf("Error: N must be less than D*(D-1)+1\n");
        return 1;
    }

    DiffCover diff_cover;
    diff_cover.n = n;
    diff_cover.d = d;
    diff_cover.threshold = threshold;
    diff_cover.d_minus_1 = d - 1;
    diff_cover.d_times_d_minus_1 = d * (d - 1);
    diff_cover.n_minus_d = n - d;
    diff_cover.n2 = n / 2;
    diff_cover.n1 = n / 2 - d * (d - 1) / 2;
    diff_cover.size_n = (n / 2 + 1) * sizeof(int8_t);

    for (int j = 0; j <= d; j++)
        diff_cover.a[j] = 0;

    diff_cover.a[d] = n;
    diff_cover.a[0] = 0; // for convenience

    Init(&diff_cover);
    return 0;
}
