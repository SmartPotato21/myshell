#include <stdio.h>      
#include <stdlib.h>    

char* read_line();   
char** split_line();

typedef struct {   
  char** words;           
  int count;       
} tokens; 


/*  example of tokens:
        
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


        tokens *Tokens = malloc(sizeof(tokens));          //init struct

        

        char* new_line = read_line();
        char** split = split_line(new_line, Tokens);

        
        //TODO: CREATE CUSTOM BASH FUNCTIONS THAT ARE CALLLED HERE

        int pid = fork();                                   //for for execvp bash
    
        if (pid == 0)            //if we are child AND forked success
        {
            
            execvp(Tokens->words[0], Tokens->words);
            exit(EXIT_FAILURE);
        } 
        wait(NULL);

        //TODO: HANDLE FORK FAILURE



        free(new_line);                                 //kill all all of them every single one
        free(split);
        free(Tokens);
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
char** split_line(char* line, tokens *cmd)
{
    char** finalreturn = malloc(5 * sizeof(char*)); //up to 5 words
    finalreturn[0] = malloc(16 * sizeof(char));     //up to 16 letters          //TODO: HANDLE OVERFLOW, HOW TO HANDLE MORE THAN 5 WORDS??
    
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

    cmd->count = word_index+1;


    word_index++;
    while(word_index <= 4)                                  //leave unused tokens as NULL
    {
        finalreturn[word_index] = NULL;
        word_index++;
    }


    cmd->words = finalreturn;                           //point struct to new variable

    return finalreturn;                                 //TO free later
}

int main() 
{
    shell_loop();
    return 0;
}
