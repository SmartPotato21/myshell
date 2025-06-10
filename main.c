#include <stdio.h>      
#include <stdlib.h>    

char* read_my_line();   

void shell_loop() {
    while (1) {
        printf("customshell> ");
        char* new_line = read_my_line();
        printf("typed: %s\n", new_line);  
        free(new_line);
    }
}

char* read_my_line() {
    size_t bufsize = 64;
    char *buffer = malloc(bufsize);         // allocate buffer size

    if (!buffer) {exit(EXIT_FAILURE);}

    int c;
    size_t i = 0;

    while (1) {
        c = getchar();

        if (c == '\n' || c == EOF) 
        {                                   //return on submission or EOF
            buffer[i] = '\0';
            return buffer;
        }

        buffer[i++] = c;                //parse input

        
        if (i >= bufsize) 
        {
            bufsize += 64;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {exit(EXIT_FAILURE);}
        }
    }
}

int main() {
    shell_loop();
    return 0;
}
