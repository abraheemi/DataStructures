/***********************************
* Author: Abraheem Irheem
*
* Class: CS 251, FALL 2014
*
* System: g++ on Ubuntu 64bit
*
* Program #5; Rhymes
*
* This program implements a Trie to store and search
* for words based on their suffixes, and it is done 
* using an array of chars which act as hash indexes
* for each of the 26 letters of the alphabet. 
* 
* This implementation can leave a lot of unused memory
* in the bottom of the trie because the only words that
* will be sharing the array are ones with the same length
* and the same suffix.
*
* There is an improved version of this trie which uses a 
* linked list with a left-child right-parent implementation
* which uses memory only when needed.
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
//const int WordLength = 26000; 
//const int WordLength = 25144;


//---------------------------------------------------------------------------
// This is the Trie structure
struct Node{
	char letter; // A letter
	bool isWord; // Marks when current letter is the start of a word
	Node* alphabet[Alpha]; // 26 Node pointers
	int mark; // FOR DEBUGGING
};

//---------------------------------------------------------------------------
// Struct to store all matching words
struct List{
	char str[30]; // Max word size
	List *next;
};

//---------------------------------------------------------------------------
// Stack to store characters until a word is formed
// after a word is formed, the stack is printed to give the word
struct Stack
{
	Node *trie; // Stack uses the data in the node already created
	Stack *next;
};


int marker = 0; // FOR DEBUGGING
int counter = 0; // Counts number of words found


//===========================================================================
void printInfo(){
  	printf("\nAuthor: Abraheem Irheem\nProgram #5: Rhymes\n");
  	printf("This program implements a Trie to store and search for words based\n");
  	printf("on their suffixes\n\n");

}


//===========================================================================
// Allocates memory for root node which will be empty and 
// initializes all Node pointers to NULL
void initializeTrie(Node* &root){
	root = (Node*)malloc(sizeof(Node));
  	root->letter = '\0';
  	root->isWord = false;
  	for(int i=0; i<Alpha; i++)
  		root->alphabet[i] = NULL;
}


//===========================================================================
// Initializes the 26 Node pointers to NULL
void childToNull(Node* &p){
	for(int i=0; i<Alpha; i++)
		p->alphabet[i] = NULL;
}


//===========================================================================
// Pushes the Trie node along with its data (letter, isWord, and alphabet[26])
void push(Stack* &top, Node *root){
	Stack *p = (Stack*)malloc(sizeof(Stack));
	p->trie = root;
	p->next = top;
	top  = p;
}


//===========================================================================
// Pops the top letter in the stack as we traverse back in the Trie in DFS
void pop(Stack* &top){
	Stack *p = top;
	top = top->next;
	free(p);
}


//===========================================================================
// Prints the stack letter by letter to form a string, but the suffix in not
// included. The suffix is taken care of after the call to this function
void printStack(Stack *top){
	while(top != NULL){
		printf("%c", top->trie->letter);
		top  = top->next;
	}
}


//===========================================================================
// This functions creates the Trie by inserting the new word letter by letter
// into their appropriate indexes in the Node pointers
void insertWord(Node* &root, char *word){
  int i, index;
  Node *p = root;

  	int len = strlen(word);
	for(i=0; i<len; i++){
		index = word[i] - 'a';
		if(p->alphabet[index] == NULL){
			p->alphabet[index] = (Node*)malloc(sizeof(Node));
			p->alphabet[index]->letter = word[i];
			p->alphabet[index]->isWord = false; // Not a word yet

			marker++; // FOR DEBUGGING
			p->mark = marker; // FOR DEBUGGING
 			//printf("marker %d\n", marker); // FOR DEBUGGING

			p = p->alphabet[index]; // Advance to next node
 			childToNull(p); // Initialize child pointers to NULL
		}
		else
			p = p->alphabet[index]; // Advance to next node
		
		if(i == len-1)
			p->isWord = true; // Last letter entry makes it a word
	}

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
// Read from the dictionary file into an array, only keeping words that 
// are the correct length.
void readDictionary( Node* &root){

  ifstream inStream; // input file stream
  char fileName[] = "dictionary.txt";	// Input file name
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
 			insertWord(root, s); // Insert into Trie
 			//printf("marker %d\n", marker); // FOR DEBUGGING
 			//printf("%d\n", size); // FOR DEBUGGING
 			//printf("%s\n", s); // FOR DEBUGGING
		}
	}
   	inStream.close(); // close the input file stream
}


//===========================================================================
// Not used
void storeWord(List* &lst, Stack *top, char *suffix){
	List *p = (List*)malloc(sizeof(List));
	int i = 0 ;
	while(top != NULL){
		p->str[i] = top->trie->letter;
		top = top->next;
		i++;
	}
	strcat(p->str, suffix);
	p->next = lst;
	lst = p;
	printf("%s\n", lst->str);
}


//===========================================================================
// Depth first search to print all words with the given suffix
void depthFirstSearch(Node *root, Stack* &top, char *suffix){

	for(int i=0; i<Alpha; i++){
		if(root->alphabet[i] != NULL){
			push(top, root->alphabet[i]);

			if(top->trie->isWord){
				//counter++; // Global variable to count words
				//storeWord(lst, top, s);
				printStack(top);
				printf("%s ", suffix);
				//printf("\n");
			}
			depthFirstSearch(root->alphabet[i], top, suffix);		
			pop(top);		
		}
	}
}


//===========================================================================
// Uses Depth-First search to count number of matching words
void countWords(Node *root){
	for(int i=0; i<Alpha; i++){
		if(root->alphabet[i] != NULL){

			if(root->alphabet[i]->isWord){
				counter++; // Global variable to count words
			}
			countWords(root->alphabet[i]);		
		}
	}
}


//===========================================================================
// Traverses the Trie to check if suffix exists and sets the root
// node to the last suffix read.
// Calls depth-first search (DFS) on Trie given the suffix.
bool search(Node* root, char *suffix){	
  Stack *top = NULL; // Stack to keep track of characters and print them
  List *lst = NULL; // Not used
  int len = strlen(suffix);
  bool suffixIsWord = false;
  Node *tmpRoot = root;
  	// Traverses the Trie to check if suffix exists and sets the root
    // node to the last suffix read
    for(int i=0; i<len; i++){
    	int index = suffix[i] - 'a';
    	if(tmpRoot->alphabet[index] == NULL){
    		printf("Suffix does not exist\n");
    		exit(0);
    	}
    	// If the suffix is itself a word
    	if(tmpRoot->alphabet[index]->isWord && i == len-1){
    		suffixIsWord = true;
    		counter++;
    	}
    	tmpRoot = tmpRoot->alphabet[index];
    }
    //Node *p = root; // Used to traverse the Trie the first time for the count
    printf("\n\n");

	strReverse(suffix);
	countWords(tmpRoot); // Counts number of matches
	printf("Found %d words\n\n", counter);
    depthFirstSearch(tmpRoot, top, suffix);
    if(suffixIsWord)
    	printf("%s", suffix); // Prints suffix if it is itself a word
    
    return suffixIsWord;
}


// NOT WORKING YET 
// TODO
void destroyTrie(Node* &root){
	int i;
	for(i=0; i<Alpha; i++){
		if(root->alphabet[i]->alphabet[i] != NULL)
			destroyTrie(root->alphabet[i]);
		free(root->alphabet[i]->alphabet[i]);
	}
}


//###########################################################################
//===========================================================================
// MAIN
int main(void){
  int i;
  Node *root ;
  
  	printInfo();
  	// Initialize Trie root node
  	initializeTrie(root);

	readDictionary(root);

    char str[10]; // Max suffix length
    printf("Enter suffix: ");
    fgets(str, 10, stdin);

    int len = strlen(str);
    str[len-1] = '\0';
    strReverse(str);
    len = strlen(str);
    search(root, str);
    //destroyTrie(root); // TODO

  	printf("\n\n");
  return 0;
}

