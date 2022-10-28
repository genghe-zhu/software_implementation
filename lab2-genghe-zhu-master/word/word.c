/* 
 * words.c - a program to print out every word
 *
 * Input: 1 or more arguments
 * Output: prints a sequence of lines, with exactly one word on each output line 
 *
 * Exit status: 
 * 0 = no error
 * 1 = file does not exist
 *
 *
 * CS50, Summer 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototype *declarations*
int handleFile(char filename[]);
void handleStdin();

// Main function - ask for a guess, quit if it matches the answer and keep asking otherwise
int main(int argc, char *argv[]) 
{

    if (argc == 1) {
        handleStdin();
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                handleStdin();
            } else {
                int j = handleFile(argv[i]);
                if (j == 1) {
                    return 1;
                }
            }
        }
    }

    // exit status
    return 0;
  
}

// read in file and print out words
int handleFile(char filename[]) 
{
    //create a file pointer and try to open it
    FILE *fp;
    fp = fopen(filename, "r");

    // check if file readable
    if((fp=fopen(filename, "r"))==NULL) {

        //error-handling. 
        fprintf(stderr, "failed to open %s", filename);
        return 1;
	}

    // flag makes sure do not print multiple new lines for multiple spaces
    int flag = 0;

    // loop through all the characters in the file
    char ch;
    while((ch=fgetc(fp)) != EOF) {
        if ((ch == ' ' || ch == '\n') && flag == 0) {
            printf("\n");
            flag++;
        // checks that ch is a letter    
        } else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            flag = 0;
            printf("%c", ch);
        }
    }
    
    // if the last line is not a new line, make sure word from next file start from new line
    if (flag == 0) {
        printf("\n");
    }

    fclose(fp);
    return 0;
}

// read in stdin and print out words
void handleStdin() 
{
    // flag makes sure do not print multiple new lines for multiple spaces
    int flag = 0;

    // loop through all the characters in the file
    int i;
    while ((i = getchar()) != EOF) {
        // cast i into a character
        char ch = (char) i;
        if ((ch == ' ' || ch == '\n') && flag == 0) {
            printf("\n");
            flag++;
        // if the last line is not a new line, make sure word from next file start from new line    
        } else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            flag = 0;
            printf("%c", ch);
        }
    }

    // if the last line is not a new line, make sure word from next file start from new line
    if (flag == 0) {
        printf("\n");
    }   
}

