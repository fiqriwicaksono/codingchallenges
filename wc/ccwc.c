#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    FILE *file = NULL;
    unsigned long size = 0;
    unsigned long words = 0;
    unsigned long lines = 0;
    int inWord = 0; // Flag for tracking word boundaries

    // Handle no file argument
    if (argv[argc-1][0] != '-') {
        file = fopen(argv[argc-1], "r");
    } else {
        file = stdin;
    }

    if (file==NULL) {
        printf("Input is null!");
        return -1;
    }

    // Process options
    int showSize = 0, showWords = 0, showLines = 0;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-c")==0) {
            showSize = 1;
        } else if (strcmp(argv[i], "-w")==0) {
            showWords = 1;
        } else if (strcmp(argv[i], "-l")==0) {
            showLines = 1;
        }
    }

    if (!showSize && !showWords && !showLines) {
        showSize = showLines = showWords = 1;
    }

    // Read through the files and count everything
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size += bytesRead;

        for (size_t i = 0; i < bytesRead; i++) {
            if (buffer[i]=='\n') {
                lines++;
            }

            if (isspace(buffer[i])) {
                inWord = 0;
            } else if (!inWord) {
                inWord = 1;
                words++;
            }
        }
    }

    if (showLines) {
        printf("%ld ", lines);
    }
    if (showWords) {
        printf("%ld ", words);
    }
    if (showSize) {
        printf("%ld ", size);
    } 
    if (argv[argc-1][0] != '-') {
        printf("%s", argv[argc-1]);
    }
    printf("\n");
    printf()

    return 0;
}