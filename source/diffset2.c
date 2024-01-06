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
#define MAX_N 100

#define MIN(a, b) ((a) <= (b))? (a) : (b)

//-------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------
int N, D;
uint8_t a[MAX], b[MAX];
int THRESHOLD;
int D_MINUS_1;
int D_TIMES_D_MINUS_1;
int N_MINUS_D;
int N1;
int N2;
size_t SIZE_N;

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
void GenD(int t, int p, int tt, uint8_t diffset[]) {
    uint8_t differences[MAX_N];
    memcpy(differences, diffset, SIZE_N);

    for (int i = 0; i < t; i++) {
        int diff = a[t] - a[i];
        differences[MIN(diff, N - diff)] = 1;
    }
    if (t >= THRESHOLD) {
        int count = 0;
        for (int i = 1; i <= N2; i++) {
            if (differences[i] != 0) {
                count++;
            }
        }
        if (count < N1 + tt) {
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

            GenD(t1, p, tt1, differences);
            if (b[t1] == 0) {
                b[t1] = 1;
                GenD(t1, t1, tt1, differences);
            }
            tail = max - 1;
        }
        for (int j = tail; j >= a[t] + 1; j--) {
            a[t1] = j;
            b[t1] = 1;
            GenD(t1, t1, tt1, differences);
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
    SIZE_N = (N2 + 1)  * sizeof(uint8_t);

    // for (i = 0; i <= N; i++) {
    //     matrix[i][i] = 0;
    //     for (j = 0; j < i; j++) {
    //         matrix[i][j] = i - j;
    //         matrix[j][i] = N - i + j;
    //     }
    // }

    uint8_t differences[MAX_N];
    memset(differences, 0, SIZE_N);
    differences[0] = 1;

    for (j = N - D + 1; j >= (N - 1) / D + 1; j--) {
        a[1] = j;
        b[1] = 1;
        GenD(1, 1, 1, differences);
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
