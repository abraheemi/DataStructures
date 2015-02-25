/***********************************
* Author: Abraheem Irheem
*
* Class: CS 251, FALL 2014
*
* System: g++ on Ubuntu 64bit
*
* Program #6; Binary Trie
*
* This program implements a Trie to store and search
* for words based on their suffixes.
* 
************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
using namespace std;


#define Alpha 26
const int MinLength = 2;      // minimum word size
//const int MaxLength = 10;     // maximum word size 
const int MaxLength = 30;     // maximum word size 
const int WordLength = 30;      


//---------------------------------------------------------------------------
// This is the Trie structure
struct Node{
	char letter; // A letter
	bool isWord; // Marks when current letter is the start of a word
	Node* leftChild;
	Node* rightSibling;
	//int mark; // FOR DEBUGGING
};


//---------------------------------------------------------------------------
// Stack to keep track of letters in order to print them
struct Stack{
	char ch;
    Node *trie;
	Stack *next;
};


//===========================================================================
// Push the node that contains the letter
void push(Stack* &top, Node *c){
   Stack *p = (Stack*)malloc(sizeof(Stack));
    p->trie = c;
    p->next = top;
    top = p;
}


void pop(Stack* &top){
    Stack *p = top;
    top = top->next;
    free(p);
}


//===========================================================================
// Prints whatever is in the stack which should be a word
void printStack(Stack *top){
    while(top != NULL){
        printf("%c", top->trie->letter);
        top = top->next;
    }
    //printf("\n");
}


//===========================================================================
/* Clear input until next End of Line Character - \n */
void clearToEoln(){
  int ch;
 
  do {
      ch = getc(stdin);
    }
  while ((ch != '\n') && (ch != EOF));

}


//===========================================================================
/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar (){
  int ch;

 	ch = getc(stdin);
 	if (ch == EOF)
   		return ch;
 	while (isspace (ch)){
	    ch = getc(stdin);
    	if (ch == EOF)
      	return ch;
   	}
 	return ch;
}


//===========================================================================
/* read in the next Positive Integer or error:    */
/* This is based on the Mathematical definition of a Postive Integer */
/*    zero is not counted as a positive number */ 
int getPosInt (){
  int value = 0;

    /* clear white space characters */
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch)){
        if ('\n' == ch)  /* error \n ==> no integer given */
            return 0;
        if (!isspace(ch)) /*error non white space ==> integer not given next*/{
            clearToEoln();
            return 0;
        }
        ch = getc(stdin);
    }

    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch)){
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }

    ungetc (ch, stdin);  /* put the last read character back in input stream */

    /* Integer value of 0 is an error in this program */
    if (0 == value)
        clearToEoln();
   
    return value;
}


//===========================================================================
/* read in the name until the end of the input */
char *getName(){
  /* skip over the white space characters */
  int ch;
  ch = getc(stdin);
  while (isspace(ch)){
      if ('\n' == ch)  /* error \n ==> no integer given */
        return NULL;
      ch = getc(stdin);
    }

  char *word;
  int size;
  size = 10;
  word = (char *) malloc (sizeof(char) * size);
  
  // read in character-by-character until the newline is encountered
  int count = 0;

  while (ch != '\n'){
      if (count+1 >= size){
          // to grow an array to make it "dynamically sized" using malloc
          char* temp;
          int i;
          size = size * 2;
          temp = (char *) malloc (sizeof(char) * size);
       
          // printf ("Growing array from size %d to size %d\n", count, size);
          // copy the characters to the new array
          for (i = 0 ; i < count ; i++)
              temp[i] = word[i];

          free (word);
          word = temp;
        }

      word[count] = ch;
      count++;
      word[count] = '\0';

      // read next character
      ch = getc(stdin);
    }

  if (count > 30){
      count = 30;
      word[count] = '\0';
    }
 
  /* clear ending white space characters */
  while (isspace (word[count-1])){
      count--;
      word[count] = '\0';
    }

  return word;
}


void printInfo(){
    printf("\nAuthor: Abraheem Irheem\nProgram #6: Binary Trie\n");
    printf("System: Linux 64-bit, g++\n\n");
}


//===========================================================================
void printCommands(){
    printf("\n");
    printf("f <str> : Find str\n");
    printf("p <n>   : Print next n words\n");
    printf("a <str> : Add str\n");
    printf("d <str> : Delete str\n");
    printf("?       : Help\n");
    printf("x       : Exit\n");
    printf("Your instruction: ");
}


//===========================================================================
void printHelpMenu(){
    printf("\n");
    printf("f <str> : Find the string str in the trie\n");
    printf("p <n>   : Print next n words starting at the current position\n");
    printf("a <str> : Add string str into the trie\n");
    printf("d <str> : Delete the string str from the trie\n");
    printf("?       : Display the help menu\n");
    printf("x       : Exit the program\n");
    clearToEoln();
}


//===========================================================================
// Convert word to lower case
void convertToLowerCase( char theWord[], const int size){
   	// convert dictionary word to lower case
   	for (int i=0; i<size; i++) {
      	theWord[i] = tolower(theWord[i]);
   	}
}


//===========================================================================
// Reverses the string Note:changing the orginal string
char * strReverse(char *str){
  char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}


//===========================================================================
// Checks if the whole word contains any non-alphabetical characters
bool isAlpha(char word[], int size){
	for(int i=0; i<size; i++){
		if( !isalpha(word[i]) )
			return false; // Contains NON-alphabetical character/s
	}
	return true; // Contains ALL-alphabetical characters
}


//===========================================================================
// Inserts a word into the tree backwards
void insertWord(Node* &root, char* word, int len){
  Node *p = root;
  Node *parent;
  bool isword = false;
  bool found;
  int i;

    for(i=0; i<len; i++){
        // The node at the end of each level should point back to the parent
        found = false; // Reset bool
        parent = p;
        if(i == len-1)
            isword = true;
        // Assume leftChild nodes are levels
        // If there exists at least one leftChild node from current node
        if(p->leftChild != NULL){
            p = p->leftChild;
            // Check if the letter is at the current level and travel
            // to that node. The right-most node's rightSibling is always
            // equal to NULL
            while(p->rightSibling->rightSibling != NULL){
                if(p->letter == word[i]){
                    found = true;
                    break; // Letter is found
                }
                //else // Letter not found yet
                p = p->rightSibling;
            }
            // In case while loop does not execute
            if (p->letter == word[i])
                found = true;
            // If the letter was not in the current level, add it to the
            // end of the list. At this point, If the if-statement is taken,
            // p is pointing at the second last node in the current 
            // list/level right before the empty node.
            if(p->rightSibling->rightSibling == NULL && !found){
                Node *newNode = (Node*)malloc(sizeof(Node));
                newNode->letter = word[i];
                newNode->isWord = isword;
                // Every leaf node's leftChild is NULL
                newNode->leftChild = NULL;
                // newNode is inserted before the empty node
                newNode->rightSibling = p->rightSibling;
                p->rightSibling = newNode;
                // Advance pointer because letters that come after should go
                // under the newest node since they are part of the same word
                p = newNode;
            }
        }
        else{ // If p->leftChild == NULL (No child pointers)
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->letter = word[i];
            newNode->isWord = isword;
            // Now create the empty node that points back to the parent
            newNode->rightSibling = (Node*)malloc(sizeof(Node));
            newNode->rightSibling->letter = '\0';
            newNode->rightSibling->isWord = false;
            newNode->rightSibling->rightSibling = NULL;
            newNode->rightSibling->leftChild = parent;
            // If it's the first node in the trie
            if(root->leftChild == NULL)
                root->leftChild = newNode;
            p->leftChild = newNode;
            p = p->leftChild; // Advance pointer
        }
        if(i == len-1){
            // Make sure last letter in reversed word makes it a word
            // if it's not already true. This could occur when inserting
            // a word that is a subset of an existing larger word.
            p->isWord = isword;
        }

    }
}


//===========================================================================
// Read from the dictionary file into an array, only keeping words that 
// are the correct length.
void readDictionary( Node* &root){

  ifstream inStream; // input file stream
  char fileName[] = "dictionary3.txt";	// Input file name
  char tempString[MaxLength+1];	// stores a single string
  char *s = (char*)malloc(sizeof(char)*MaxLength+1);
  int  size, i;

   	inStream.open( fileName);
   	assert( ! inStream.fail() );  // make sure file open was OK

	cout << "\n Reading dictionary file from " << fileName << "\n";	
	while ( inStream >> tempString ){
 		size = strlen( tempString);

 		// Filter out words with non-alphabetical characters
 		if(isAlpha(tempString, size) && size != 0){
	
      		convertToLowerCase( tempString, size);
      		strReverse(tempString);
			strcpy( s, tempString);
 			insertWord(root, s, size); // Insert into Trie
 			//printf("marker %d\n", marker); // FOR DEBUGGING
 			//printf("%d\n", size); // FOR DEBUGGING
 			//printf("%s\n", s); // FOR DEBUGGING
		}
	}
   	inStream.close(); // close the input file stream
}


// Implements depth-first search
void dfs(Node *root){
    Node *p = root->leftChild;
    while(p != NULL){
        dfs(p);
        p = p->rightSibling;
    }
    printf("%c ", root->letter);
}


//===========================================================================
// Searches for given string and returns true if found and false otherwise
bool search(Node* root, char *str, Node* &p){
  p = root;
  int len = strlen(str);
  int i;
  bool suffixIsWord = false;
  //bool stringExists = false;

    strReverse(str);
	for(i=0; i<len; i++){
        //printf("%d\n",(p==NULL)); // FOR DEBUGGING
		
        if(p->leftChild == NULL)
            return false;
		
        p = p->leftChild;
		while(p->rightSibling != NULL){
            //printf("%c %c\n", p->letter, str[i]); // FOR DEBUGGING

			if(p->letter == str[i]){
				//printf("%c\n", p->letter);
				// If the string itself is a word
				//if(i == len-1 && p->isWord)
				//	suffixIsWord = true;
				break; // Goes back to for loop
			}
			else
				p = p->rightSibling;
		}
        if(p->rightSibling == NULL){
            //printf("BREAK\n"); // FOR DEBUGGING
            return false;
        }

	}
    //printf("the letter is: %c\n", p->letter); // FOR DEBUGGING
    return true;
}


void traverser(Node *s){
    while(s->letter != '*'){
        printf("%c", s->letter);
        while(s->rightSibling != NULL){
            s = s->rightSibling;
        }
        s = s->leftChild;
    }
}


//===========================================================================
// Used when user gives the command p n
// Prints the next n words starting from the current position of pointer t
// pSuf points to the current suffix
// t points to the last word that it traverses to/printed
void printNextNWords(int n, Node* &pSuf, Node* &t){
  //t = pSuf; // t starts from where the suffix is
  int i;
  Node *s; // Used to print words by traversing back to parent

    //strReverse(suf);
    //if(t->leftChild != NULL)
    //    t = t->leftChild;

    //else
    //    t = t->rightSibling;
    //push(top, t);

    i = 0;
    while(t != pSuf && t != NULL){

        if(t->leftChild != NULL && t->rightSibling != NULL){
            t = t->leftChild;
        }
        else if(t->leftChild == NULL && t->rightSibling != NULL){
            
            if(t == pSuf) // ADDED
                return;

            if(t->isWord){
                s = t;
                traverser(s);
                printf("\n");
                i++;
                t = t->rightSibling;
            }
        }
        else{
            t = t->leftChild; // Now its back to parent
            if(t == pSuf){
                if(t->isWord){
                    s = t;
                    traverser(s);
                }
                printf("\nNo more words**\n");
                return;
            }

            if(t->isWord){
                s = t;
                traverser(s);
                printf("\n");
                i++;
            }
            t = t->rightSibling;
        }

        if(i == n) // Prints only n words
            return; // Exits this function afterwords
    }
    printf("No more words\n"); 
    //printf("the letter is: %c\n", t->letter);
}


void recursiveRemoval(Node* &p){
    Node *tmp;
    Node *r;
    int counter;
    //if(p->rightSibling != NULL)
    //    recursiveRemoval(p->rightSibling);
    
    while(p->rightSibling != NULL){
        p = p->rightSibling;
    }
    //else{
        p = p->leftChild; // Back to parent
        r = p; // Keeps track of parent
        //while(true)
            // If the first node in the list is not a word
            if( ! p->leftChild->isWord && p->leftChild == NULL){
                tmp = p->leftChild;
                p->leftChild = p->leftChild->rightSibling;
                free(tmp);
                // If the node was pointing to the empty node
                if(p->leftChild->rightSibling == NULL){ // The empty node
                    tmp = p->leftChild;
                    p->leftChild = NULL;
                    free(tmp);
                }
            }
            // We are back at another parent node
            else{
                counter = 0;
                p = p->leftChild;
                while(p->rightSibling != NULL){
                    if(p->rightSibling->isWord)
                        counter++;
                    if( ! p->rightSibling->isWord && 
                        p->rightSibling->leftChild == NULL){

                        tmp = p->rightSibling;
                        p->rightSibling = p->rightSibling->rightSibling;
                        free(tmp);
                    }

                }
                if(counter == 0){ //If no words left, free the empty node
                    tmp = r->leftChild;
                    r->leftChild = NULL;
                    free(r);
                }
            }
    //}
}


void traceBackRemoval(Node* &p){
    Node *q = p;

    while( ! p->rightSibling->leftChild->isWord && 
        p->rightSibling->leftChild->rightSibling->letter == '\0'){

        q = p;
        p = p->rightSibling->leftChild;
        free(q);
    }
    /*
    // Traverse to parent
    while(p->rightSibling != NULL){
        p = p->rightSibling;
    }
    p = p->leftChild; // Now its at parent
    if( ! p->leftChild->isWord ){

    }

    while(p->rightSibling != NULL){
        if(!p->isWord && p->leftChild != NULL){

        }
        p = p->rightSibling;
    }*/
}


//===========================================================================
// Removes string depending whether the leftChild or rightSibling is pointing
// at it
void removeString(Node* &p, char c, bool flag){
    if(flag){
        if( p->leftChild->rightSibling->rightSibling != NULL &&
            p->leftChild->leftChild != NULL){
    
            p->leftChild->isWord = false;
        }
        // If this linked list only has two nodes, the one with the
        // letter and the empty one
        else if(p->leftChild->leftChild == NULL &&
                p->leftChild->rightSibling->rightSibling == NULL){
    
            Node *tmp = p->leftChild->rightSibling;
            p->leftChild->rightSibling = p->leftChild->rightSibling->rightSibling;
            free(tmp);  // Free the empty node
            tmp = p->leftChild;
            p->leftChild = NULL;
            free(tmp); // Free the letter node
            //recursiveRemoval(p);
            //traceBackRemoval(p);
        }
    }
    else{
        while(p->rightSibling->letter != c){
            p = p->rightSibling;
        }
        if(p->rightSibling->leftChild == NULL){
            Node *tmp = p->rightSibling;
            p->rightSibling = p->rightSibling->rightSibling;
            free(tmp);
        }
        else{
            p->rightSibling->isWord = false;
        }
    }

}


//===========================================================================
// Deletes given string and resets the traverser to point to root
// p is the traverser
void deleteString(Node* &root, Node* &p, char *str){
  int len = strlen(str);
  int i;
  bool flag;

    //strReverse(str);
    // Reversesthe string at the same time
    if(!search(root, str, p)){
        printf("String does not exist\n");
        return;
    }

    // At this point, str must exist in the trie
    p = root;
    for(i=0; i<len; i++){

        if(i == len-1){
            if(p->leftChild->letter == str[i]){
                flag = true;
                removeString(p, str[i], flag);
                return;
            }
        }

        p = p->leftChild;
        while(p != NULL){
            if(i == len-1){
                if(p->rightSibling->letter == str[i]){
                    flag = false;
                    removeString(p, str[i], flag);
                    return;
                }
            }

            if(p->letter == str[i]){
                //printf("%c\n", p->letter);
                // If the string itself is a word
                //if(i == len-1 && p->isWord)
                //    bool suffixIsWord = true;
                break; // Goes back to for loop
            }
            else
                p = p->rightSibling;
        }
    }

}


//###########################################################################
//===========================================================================
// MAIN
int main(void){
  Node *root = (Node*)malloc(sizeof(Node)); // The Trie
  Node *pSuf; // Pointer to the end of the current suffix
  Node *t; // Pointer to the last letter traversed to/printed so far
  //Stack *top = NULL; // Stack to keep track of letters and print them
  char *str; // For user input
  char *newWord; // When user enters a new word
  char *delWord;
  char c; // For user command
  int len, n; // n is when user enters p n

    printInfo();

    root->letter = '*';
    root->isWord = false;
    root->leftChild = NULL;
    root->rightSibling = NULL;

  	readDictionary(root);
	while(true){
        printCommands();
        c = getNextNWSChar ();
        c = tolower(c);
        
        if(c == 'f'){ // Find string in trie
            str = getName();
            //len = strlen(str);
            //printf("string: %s\nlen: %d\n", str, len);
            if(search(root, str, pSuf)){
                printf("String exists\n");
                t = pSuf->leftChild;
            }
            else
                printf("String does not exist\n");
        }
        else if(c == 'p'){ // Print next n words from current pointer position
            n = getPosInt();
            //printf("N = %d\n", n);
            printNextNWords(n, pSuf, t);
            //printf("Command not implemented yet\n");
            clearToEoln(); // Clears buffer
        }
        else if(c == 'a'){ // Add a new string to the list
            newWord = getName();
            strReverse(newWord);
            len = strlen(newWord);
            insertWord(root, newWord, len);
        }
        else if(c == 'd'){
            delWord = getName();
            deleteString(root, t, delWord);
            t = NULL;
            //printf("Command not implemented yet\n");
            //clearToEoln(); // Clears buffer           
        }
        else if(c == '?'){
            printHelpMenu();
        }
        else if(c == 'x'){
            printf("Quitting program...\n");
            exit(0);
        }
        else{
            printf("Error: %c is an incorrect command\n", c);
            clearToEoln(); // Clears buffer
        }
    }

  return 0;
}

