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

#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define MAX_N 200

//-------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------
int N, D, type, NECK = 0, LYN = 0;
int a[MAX], b[MAX];
int matrix[MAX_N][MAX_N];
int differences[MAX_N];

//-------------------------------------------------------------
void PrintD(int p) {
    int next, min;

    /* Determine minimum position for next bit */
    next = (D / p) * a[p] + a[D % p];
    if (next < N)
        return;

    /* Determine last bit */
    min = 1;
    if ((next == N) && (D % p != 0)) {
        min = b[D % p] + 1;
        p = D;
    } else if ((next == N) && (D % p == 0))
        min = b[p];

    for (b[D] = min; b[D] < 2; b[D]++) {
        if (LYN && (N % a[p] == 0) && (a[p] != N)) {
        } else {
            // print a
            for (auto i = 1; i <= D; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
            exit(0);

            // }
            // printf("\n");
        }
        p = D;
    }
}

/*-----------------------------------------------------------*/
// FIXED DENSITY
/*-----------------------------------------------------------*/
void GenD(int t, int p) {
    int j, max, tail, count;

    if (t >= (D - 1) / 2) {
        for (auto i = 0; i < N; i++) {
            differences[i] = 0;  // clear
        }
        for (auto i = 0; i <= t; i++) {
            for (auto j = 0; j <= t; j++) {
                differences[matrix[a[i]][a[j]]] = 1;
            }
        }
        count = 1;
        for (auto i = 1; i < N; i++) {
            if (differences[i] != 0) {
                count += 1;
            }
        }
        if (count + D * (D - 1) - (t + 1) * t < N) {
            return;
        }
    }

    if (t >= D - 1)
        PrintD(p);
    else {
        tail = N - (D - t) + 1;
        max = a[t - p + 1] + a[p];
        if (max <= tail) {
            a[t + 1] = max;
            b[t + 1] = b[t - p + 1];

            GenD(t + 1, p);
            if (b[t + 1] == 0) {
                b[t + 1] = 1;
                GenD(t + 1, t + 1);
            }
            tail = max - 1;
        }
        for (j = tail; j >= a[t] + 1; j--) {
            a[t + 1] = j;
            b[t + 1] = 1;
            GenD(t + 1, t + 1);
        }
    }
}

/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
void Init() {
    int i, j;

    for (j = 0; j <= D; j++)
        a[j] = 0;
    a[D] = N;
    a[0] = N;

    for (i = 1; i <= N; i++) {
        matrix[i][i] = 0;
        for (j = 1; j < i; j++) {
            matrix[i][j] = i - j;
            matrix[j][i] = N - i + j;
        }
    }
    for (j = N - D + 1; j >= (N - 1) / D + 1; j--) {
        a[1] = j;
        b[1] = 1;
        GenD(1, 1);
    }
    printf("No solution is found.\n");
}

//------------------------------------------------------
void usage() {
    printf("Usage: necklace [type] [n] [d]\n");
}
//--------------------------------------------------------------------------------
int main(int argc, char **argv) {
    if (argc < 4) {
        usage();
        return 1;
    }
    sscanf(argv[1], "%d", &type);
    sscanf(argv[2], "%d", &N);
    sscanf(argv[3], "%d", &D);

    if ((type != 2) && (type != 22)) {
        usage();
        return 1;
    }

    // NECKLACES                                LYNDON WORDS
    // -------------                            -------------
    // 2.  Fixed-density                        22. Fixed-density

    if (type == 2) {
        NECK = 1;
    } else if (type == 22) {
        LYN = 1;
    }

    if (N > D * (D - 1) + 1) {
        printf("Error: N must be less than D*(D-1)+1\n");
        return 1;
    }

    Init();
    return 0;
}
