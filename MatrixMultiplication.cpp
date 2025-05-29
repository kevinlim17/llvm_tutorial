#include <stdio.h>

void multiply_matrices(int m1[][10], int m2[][10], int m3[][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            m3[i][j] = 0;
            for (int k = 0; k < 10; k++) {
                m3[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main() {
    int matrix1 [10][10];
    int matrix2 [10][10];
    int matrix3 [10][10];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }
    }

    multiply_matrices(matrix1, matrix2, matrix3);

    printf("Matrix multiplication result:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", matrix3[i][j]);
        }
        printf("\n");
    }
}