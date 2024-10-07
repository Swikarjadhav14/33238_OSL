// Process2.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <unistd.h> 
 
#define FIFO1 "/tmp/fifo1" 
#define FIFO2 "/tmp/fifo2" 
#define BUFFER_SIZE 1024 
#define OUTPUT_FILE "output.txt" 
 
void analyzeText(const char *text, char *result) { 
    int characters = 0, words = 0, lines = 0; 
    const char *ptr = text; 
 
    while (*ptr) { 
        characters++; 
        if (*ptr == ' ' || *ptr == '\n') words++; 
        if (*ptr == '\n') lines++; 
        ptr++; 
    } 
    words++;  // Last word 
    sprintf(result, "Characters: %d, Words: %d, Lines: %d", 
characters, words, lines); 
} 
 
int main() { 
    char input[BUFFER_SIZE]; 
    char analysis[BUFFER_SIZE]; 
    int fd1, fd2; 
    FILE *file; 
 
    while (1) { 
        // Read input from FIFO1 
        fd1 = open(FIFO1, O_RDONLY); 
        read(fd1, input, BUFFER_SIZE); 
        close(fd1); 
        printf("Received input: %s\n", input); 
 
        // Analyze the text 
        analyzeText(input, analysis); 
 
        // Write the analysis to a text file 
        file = fopen(OUTPUT_FILE, "w"); 
        fprintf(file, "%s\n", analysis); 
        fclose(file); 
 
        // Read from text file and send the content to FIFO2 
        file = fopen(OUTPUT_FILE, "r"); 
        fread(analysis, sizeof(char), BUFFER_SIZE, file); 
        fclose(file); 
 
        fd2 = open(FIFO2, O_WRONLY); 
        write(fd2, analysis, strlen(analysis) + 1); 
        close(fd2); 
    } 
    return 0; 
}