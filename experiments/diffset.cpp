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
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const auto MAX = 20;
const auto MAX_N = 70;

//-------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------
struct DiffCover {
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
    const int *begin_a;
    size_t size_n;

    DiffCover(int n, int d, int threshold)
        : n{n}, d{d}, threshold{threshold}, d_minus_1{d - 1},
          d_times_d_minus_1{d * (d - 1)}, n_minus_d{n - d}, n1{n / 2 -
                                                               d * (d - 1) / 2},
          n2{n / 2}, begin_a{&a[0]}, size_n{(n / 2 + 1) * sizeof(int8_t)} {
        for (auto j = 0; j <= d; j++)
            a[j] = 0;

        a[d] = n;
        a[0] = 0; // for convenience
    }

    //-------------------------------------------------------------
    /**
     * Prints the generated set to stdout and exits.
     */
    void PrintD() const {
        // print a
        for (auto i = 1; i <= this->d; i++) {
            printf("%d ", this->a[i]);
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
    void GenD(int t, int p, int tt, int8_t diffset[]) {
        int8_t differences[MAX_N];
        memcpy(differences, diffset, this->size_n);

        const auto at = this->a[t];
        for (auto p = this->begin_a; p != this->begin_a + t; ++p) {
            const auto diff = at - *p;
            const auto n_diff = this->n - diff;
            differences[diff <= n_diff ? diff : n_diff] = 1;
        }
        if (t >= this->threshold) {
            int8_t count = 0;
            const int8_t *begin = &differences[1];
            for (auto p = begin; p != begin + this->n2; ++p) {
                count += *p;
            }
            if (int(count) < this->n1 + tt) {
                return;
            }
        }

        const auto t1 = t + 1;
        if (t1 >= this->d)
            this->PrintD();
        else {
            auto tail = this->n_minus_d + t1;
            const auto max = this->a[t1 - p] + this->a[p];
            const auto tt1 = t1 * (t1 + 1) / 2;
            if (max <= tail) {
                this->a[t1] = max;
                this->b[t1] = this->b[t1 - p];

                this->GenD(t1, p, tt1, differences);
                if (this->b[t1] == 0) {
                    this->b[t1] = 1;
                    this->GenD(t1, t1, tt1, differences);
                }
                tail = max - 1;
            }
            for (auto j = tail; j >= at + 1; j--) {
                this->a[t1] = j;
                this->b[t1] = 1;
                this->GenD(t1, t1, tt1, differences);
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
    void run() {
        int8_t differences[MAX_N];
        memset(differences, 0, this->size_n);
        differences[0] = 1;

        for (auto j = this->n_minus_d + 1; j >= (this->n - 1) / this->d + 1;
             j--) {
            this->a[1] = j;
            this->b[1] = 1;
            this->GenD(1, 1, 1, differences);
        }
        printf("No solution is found.\n");
    }
};
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

    DiffCover diff_cover(n, d, threshold);
    diff_cover.run();
    return 0;
}
