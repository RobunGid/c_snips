#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int determinant(int *matrix, int size);
void print_matrix(const int *arr, int size);
int* cofactor(int *matrix, int size, int col, int row);
int* swap_column(int *matrix, int size, int col_num, int* column);

int main()
{
	int *matrix;
	int *free_terms;
	int size;
	printf("Enter size of square system of equations: ");
	scanf("%d", &size);
	printf("\n");
	matrix = (int*)malloc(size * size * sizeof(int));
	free_terms = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("A[%d][%d]=", i, j);
			scanf("%d", (matrix + i * size + j));
		}
	}
	for (int i = 0; i < size; i++) {
		printf("B[%d]=", i);
		scanf("%d", (free_terms + i));
	}

	int det = determinant(matrix, size);
	if (det == 0) {
		printf("No solutions\n");
		return 1;
	}
	int det_cols[size];
	int roots[size];
	printf("DetA=%d\n", det);
	for (int i = 0; i < size; i++) {
		int* swapped = swap_column(matrix, size, i, free_terms);
		det_cols[i] = determinant(swapped, size);
		roots[i] = det_cols[i] / det;
		printf("--- x_%d ---\n", i+1);
		printf("Det_%d = %d\n", i+1, det_cols[i]);
		printf("x_%d=%d\n", i+1, roots[i]);
		free(swapped);

	}

	free(matrix);
	free(free_terms);
	return 0;
}

int determinant(int *matrix, int size) {
	if (size == 1) return *matrix;
	if (size == 2) return 
		(*(matrix) * *(matrix + 3)) - (*(matrix + 1) * *(matrix + 2)); 
	int det = 0;
	for (int i = 0; i < size; i++) {
		int* cofactor_matrix = cofactor(matrix, size, i, 0);
		int sign = (i % 2 == 0) ? 1 : -1;
		det += *(matrix+i) * sign * determinant(cofactor_matrix, size-1);
		free(cofactor_matrix);
	}
	return det;
}

int* cofactor(int *matrix, int size, int col, int row) {
	int *new_matrix = (int*) malloc((size-1) * (size-1) * sizeof(int));
	int r = 0;
	for (int i = 0; i < size; i++) {
		if (i == row) continue;
		int c = 0;
		for (int j = 0; j < size; j++) {
			if (j == col) continue;
			*(new_matrix + r * (size-1) + c) = *(matrix + i * size + j);
			c++;
		}
		r++;
	}
	return new_matrix;
}

void print_matrix(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d ", arr[i * size + j]);
        }
        printf("\n");
    }
	printf("\n");
}

int* swap_column(int *matrix, int size, int col_num, int* column) {
    int* swapped = malloc(size * size * sizeof(int));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(swapped + i * size + j) = *(matrix + i * size + j);
        }
    }
    for (int i = 0; i < size; i++) {
        *(swapped + i * size + col_num) = *(column + i);
    }
    return swapped;
}
