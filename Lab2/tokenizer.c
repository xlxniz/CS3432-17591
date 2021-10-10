#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define max 1000

//checks if char is whitespace
bool delim_character(char c) {
 if((c == ' ' || c == '\t' || c == '(' ) && c != '\0') {
    return 1;
 }
 return 0;

}

//checks if char is not a whitespace
bool non_delim_character(char c){
 if((c != '\t' && c != ' ' && c != '(' && c != ')') && c != '\0') {
   return 1;
 }
 return 0;
}

// returns pointer to starting character
char *word_start(char *str){
 int i = 0;
 while(delim_character(str[i])) {
   i++;
 }
 return &str[i];
}

//retruns pointer to end character
char *end_word(char *str) {
 str = word_start(str);
 int i =0;
 while(non_delim_character(str[i])){
   i++;
 }
 return &str[i];
}
//returns number of tokens by counting the end of word
int count_tokens(char *str) {
 int count;
 for(count = 0; str != end_word(str); count++) {
   str = end_word(str);
 }
 return count;
}

// returns a array with a token in it
char *copy_str(char *inStr, short len) {
 int i;
 char *copy =    (char *)malloc(sizeof(char) * (len+1)); // create a block of memory
 for(i=0; i< len; i++) {
   copy[i] = inStr[i]; // adds each character to memory
 }
 copy[i] = '\0'; // ends the block will a zero terminator
 return copy;
}

// returns an array of words
char **tokenize(char *str) {

 int i;
 int tokens = count_tokens(str); //gets the total count of all the words
 char **array = malloc(sizeof(char *) * (tokens+1)); // creates a block or memory
 char *start = word_start(str); // gets the starting word
 // printf("%s", start_word);
 char *end = end_word(str); // gets the ending character
 //int word_len = end_word - start_word; // gets the length of the word
//    printf("%d", word_len);

 for (i = 0; i < tokens; i++) {
   array[i] = copy_str(start, end-start); // creates a char "array" and stores it in postion i of array
   start = word_start(end); // gets the new starting word
   end = end_word(start); // gets the new ending word
 }

 array[i] = 0;
 return array;
}
