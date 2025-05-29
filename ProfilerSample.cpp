#include <cstdio>
#include <cstdlib>

const int MALLOC_SIZE = 10;

int main() {
    const auto mat = (int *) malloc(MALLOC_SIZE);

    for (int i = 0; i < MALLOC_SIZE; i++) {
        mat[i] = rand();
    }

    for (int i = 0; i < MALLOC_SIZE; i++) {
        printf("%p\n", &mat[i]);
    }
    free(mat);

    return 0;
}