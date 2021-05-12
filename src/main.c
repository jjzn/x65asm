#include <stdio.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: %s file [-o output]\n", argv[0]);
        return 0;
    }

    return 0;
}
