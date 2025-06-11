#include <stdio.h>      
#include <stdlib.h>    

char* read_line();   
char** split_line();

typedef struct {   
  char** words;           
  int count;       
} commands; 


/*  example of cmds:
        
            input = grep "search" file.txt     
            cmds:
                words =   grep, "search", file.txt
                count = 3
*/

void shell_loop() 
{
    while (1) 
    {

        printf("customshell> ");


        commands *cmds = malloc(sizeof(commands));          //init struct

        

        char* new_line = read_line();
        char** split = split_line(new_line, cmds);

        
        //TODO: CREATE BASH FUNCTIONS THAT ARE CALLLED HERE


        printf("typed: %i\n", cmds->count);             //debug line


        free(new_line);                                 //kill all all of them every single one
        free(split);
        free(cmds);
        new_line = NULL;
        split = NULL;
    }
}

char* read_line() 
{
    size_t bufsize = 64;
    char *buffer = malloc(bufsize);         // allocate buffer size

    if (!buffer) {exit(EXIT_FAILURE);}

    int c;
    int i = 0;

    while (1) 
    {
        c = getchar();

        if (c == '\n' || c == EOF) 
        {                                   //return on submission or EOF
            buffer[i] = '\0';
            return buffer;
        }
        if (i == 63)
        {
            exit(EXIT_FAILURE);
        }

        buffer[i++] = c;                //parse input

        
        
    }
}
char** split_line(char* line, commands *cmd)
{
    char** finalreturn = malloc(5 * sizeof(char*)); //up to 5 words
    finalreturn[0] = malloc(16 * sizeof(char));     //up to 16 letters          //TODO: HANDLE OVERFLOW
    
    if (line == NULL)   {exit(EXIT_FAILURE);}

    char* iterator =  line;
    int word_index = 0;             //index of word, index of the next letter
    int letter_index = 0;
    
    while(*iterator != '\0')
    {
        if(*iterator != ' ')        //add on to current word
        {
            finalreturn[word_index][letter_index] = *iterator;
            letter_index++;
        }
        else
        {                           //allocate space for the new word, increment index
            letter_index++;
            finalreturn[word_index][letter_index] = '\0';
            word_index++;
            finalreturn[word_index] = malloc(16 * sizeof(char));
            letter_index = 0;
        }

        
        
        iterator++;                 //increment iterator
    }
   
    finalreturn[word_index][letter_index++] = '\0';         //adds string EOF


    cmd->words = finalreturn;                           //modify struct
    cmd->count = word_index+1;

    return finalreturn;
}

int main() 
{
    shell_loop();
    return 0;
}
