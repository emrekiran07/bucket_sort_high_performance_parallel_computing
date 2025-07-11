#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define MAX_THREADS 80

struct bucket {
    int n_elem;
    int index;
    int start;
};

// Comparison
int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Uniform distribution
void generate_uniform(int *A, int dim, int limit) {
    for (int i = 0; i < dim; i++) {
        A[i] = rand() % limit;
    }
}

// Normal distribution
void generate_normal(int *A, int dim, int limit) {
    for (int i = 0; i < dim; i += 2) {
        double u1 = ((double) rand() + 1) / ((double) RAND_MAX + 2);  
        double u2 = ((double) rand() + 1) / ((double) RAND_MAX + 2);
        double mag = sqrt(-2.0 * log(u1));
        double z0 = mag * cos(2.0 * M_PI * u2);
        double z1 = mag * sin(2.0 * M_PI * u2);

        int val0 = (int)(limit / 2 + z0 * (limit / 6));
        int val1 = (int)(limit / 2 + z1 * (limit / 6));

        A[i] = (val0 < 0) ? 0 : (val0 >= limit) ? limit - 1 : val0;

        if (i + 1 < dim)
            A[i + 1] = (val1 < 0) ? 0 : (val1 >= limit) ? limit - 1 : val1;
    }
}

// Exponential distribution
void generate_exponential(int *A, int dim, int limit) {
    double lambda = 1.0 / (limit / 10.0);
    for (int i = 0; i < dim; i++) {
        double u = ((double) rand()) / RAND_MAX;
        A[i] = (int)(-log(1 - u) / lambda);
        if (A[i] >= limit) A[i] = limit - 1;
    }
}

int main() {
    int *A, *B;
    int dim, n_buckets, i, limit = 100000, dist_choice;

    printf("Enter length of array to sort: ");
    if (scanf("%d", &dim) != 1) {
        printf("Invalid input for dim\n");
        return -1;
    }

    printf("Enter number of buckets: ");
    if (scanf("%d", &n_buckets) != 1) {
        printf("Invalid input for buckets\n");
        return -1;
    }

    printf("Choose data distribution:\n1 - Uniform\n2 - Normal\n3 - Exponential\n> ");
    if (scanf("%d", &dist_choice) != 1) {
        printf("Invalid input for distribution\n");
        return -1;  
    }

    int width = limit / n_buckets;

    A = (int *)malloc(sizeof(int) * dim);
    B = (int *)malloc(sizeof(int) * dim);

    srand(time(NULL));
    if (dist_choice == 1)
        generate_uniform(A, dim, limit);
    else if (dist_choice == 2)
        generate_normal(A, dim, limit);
    else
        generate_exponential(A, dim, limit);

    struct bucket buckets[n_buckets];
    memset(buckets, 0, sizeof(buckets));

    // Count elements per bucket
    for (i = 0; i < dim; i++) {
        int index = A[i] / width;
        if (index >= n_buckets) index = n_buckets - 1;
        buckets[index].n_elem++;
    }

    // Set bucket start positions
    buckets[0].start = 0;
    for (i = 1; i < n_buckets; i++) {
        buckets[i].start = buckets[i - 1].start + buckets[i - 1].n_elem;
    }

    // Copy start positions to index
    for (i = 0; i < n_buckets; i++) {
        buckets[i].index = buckets[i].start;
    }

    // Distribute data into buckets
    for (i = 0; i < dim; i++) {
        int index = A[i] / width;
        if (index >= n_buckets) index = n_buckets - 1;
        B[buckets[index].index++] = A[i];
    }

    double start_time = omp_get_wtime();

    // Parallel sort each bucket
    #pragma omp parallel for schedule(dynamic)
    for (i = 0; i < n_buckets; i++) {
        qsort(B + buckets[i].start, buckets[i].n_elem, sizeof(int), cmpfunc);
    }

    double total_time = omp_get_wtime() - start_time;

    // Verify 
    int sorted = 1;
    for (i = 0; i < dim - 1; i++) {
        if (B[i] > B[i + 1]) {
            sorted = 0;
            break;
        }
    }

    if (sorted)
        printf("The data is correctly sorted!\n");
    else
        printf("The data is not sorted correctly!\n");

    printf("Sorting %d elements took %f seconds\n", dim, total_time);

    free(A);
    free(B);
    return 0;
}
