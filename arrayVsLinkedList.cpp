#include <stdlib.h>
#include <stdio.h>
#include <ctime>      // For time functions
#include <math.h>     // For pow()
#include <time.h>
#include <iostream>
using namespace std;


struct Node{
  int data;
  Node* pNext;
};


void printInfo(){
	printf("Author: Abraheem Irheem\n\n");
    printf("Welcome to the Array vs Linked List comparison program. \n\n");
    printf(" Elapsed    Data Size      Array Time      List Time\n");
    printf("(seconds)   (thousands)    (seconds)       (seconds)\n");
}


// For testing
void printArray(int* array, int s){	
  int i;
	for(i=0; i<s; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}


// Add values to array in order
void addToArray( int newNumber, int * &pNewArray, int size)
{
    int i, j;
    int insert =0; 
    // Add new element into new array In Order
    for(i=0; i<size; i++){
        if(newNumber > pNewArray[i])
            insert++; // Keeps track of insert index
		else
			break;
    }  
	if(size > 0){ 
    	// shift values only when array already has at least one value
    	for(j = size; j>insert; j--){
        	pNewArray[j] = pNewArray[j-1];
		}
	}
	// Insert the new value into the correct index
    pNewArray[insert] = newNumber;
}


// Removes a value by it's index number by shifting all larger values down
void removeFromArray(int index, int* &pArray, int &size){
  int i;
	//for(i=size-1; i>index; i--){
	for(i=index; i<size;  i++){
		pArray[i] = pArray[i+1];
	}
	size--;
}


// Insert the first node
void add(Node* &pHead, int input, Node* newNode){
  Node *pTemp;
  	pTemp = newNode;
   	pTemp->data = input;
   	pTemp->pNext = pHead;
   	pHead = pTemp;
}


// Insert nodes in order
void addNode( Node * &pHead, int input, Node* newNode)
{
  Node* pTemp;
    
	// If list is empty add to front of list
	if(  pHead == NULL) {
		add( pHead, input, newNode);  
	} 
	// if number is < head node number, number goes at the beginning of the list
	if( input < pHead->data) {
		//pTemp = newNode;
		//pTemp->data = input;
		//pTemp->pNext = pHead;
		//pHead = pTemp;
		newNode->data = input;
		newNode->pNext = pHead;
		pHead = newNode;
	}   
	else {
		// Advance pointer while there are more nodes and new number is bigger than NEXT number
		pTemp = pHead;
		while ( (pTemp->pNext!= NULL) && (input > pTemp->pNext->data) ) { 
			pTemp = pTemp->pNext;
		}   
		// else number goes in middle or at end of list, after the current pTemp node
		Node *pNextNode = pTemp->pNext;   // store address of the next node (could be NULL)
		pTemp->pNext = newNode;          // get a new node, linked into place
		pTemp = pTemp->pNext;             // advance pTemp into this new node
		pTemp->data = input;              // store the data
		pTemp->pNext = pNextNode;         // make it point to the next node (or NULL)
	}   
         
}


// Delete a random node
void deleteNode(Node* &head, int index, int &listSize){
  Node *temp = head;
  int i;

	if(index == 0){ // If deleting the first index
		head = head->pNext;
	}
	else if(index == 1){ // If deleting the second index
		head->pNext = head->pNext->pNext;
	}
	else if(index == listSize-1){ // If deleting the last index
		for(i=0; i<index-1; i++){
			temp = temp->pNext;
		}
		temp->pNext = temp->pNext->pNext;
	}
	else{ // If deleting any other index
		i = 0;
		while(i<index-1){
			temp = temp->pNext;
			i++;
		}
		temp->pNext = temp->pNext->pNext;
	}
	listSize--;
}


// For testing
void displayList(Node* head){
	if(head == NULL)
		return;
	displayList(head->pNext);
	cout << head->data << " ";
}


int main()
{
  int arraySize, listSize;
  time_t beginTime = time( NULL);  // set the start time
  int i, j;

	srand((int)time(NULL));
	printInfo();	
	
    // Loop to do multiple iterations for different array sizees
    //for( i=2; i<pow(2,20); i=i*2) {
	//for(i=0; i<15000; i+=1000){ // For TA to run
	for(i=0; i<250000; i+=6000){  

        //arraySize = 30;
        arraySize = 1000 + i;
		listSize = 1000 + i;
		int s = arraySize;
    
        // allocate space for the array
        int *pArray = (int *) malloc( sizeof(int) * arraySize);
    
        // Start array timer
        clock_t startTime1 = clock();
		// Fill the array with random values in order
		for(j=0; j<arraySize; j++){
			addToArray(rand()%arraySize, pArray, j);
		}
		//printArray(pArray, arraySize);
		// Remove from a random index in the array until its empty
		for(j=0; j<arraySize; j++){
			removeFromArray(rand()%s, pArray, s);
		}
		// End array timer
		clock_t end1 = clock(); 
		// Free the array
		free(pArray);
		// End of array part
        //printf("%5.0f     %8d %15.4f\n", difftime(time( NULL), beginTime), arraySize,
		//								(end1 - startTime1)/(double)CLOCKS_PER_SEC);

		// Create an array of pointers to nodes
		Node** root = (Node **) malloc( sizeof(Node*) * listSize);
		// Allocate memory for each pointer to node
		for(j=0; j<listSize; j++){
			root[j] = (Node *) malloc( sizeof(Node));
			//root[j]->pNext = NULL;	
		}
		Node* head = NULL;
		// START LINKED LIST TIMER
        clock_t startTime2 = clock();

		//root[0]->data = rand()%listSize; // Insert first number to head of list
		for(j=0; j<listSize; j++){
			// root[0] is the pointer to head of the list
			addNode(head, rand()%listSize, root[j]);
		}

		int l = listSize; // l will change as we shrink listSize
		for(j=0; j<listSize; j++){
			deleteNode(head, rand()%l, l);
		}

		// END LINKED LIST TIMER
		clock_t end2 = clock(); 

        // Display number of seconds elapsed.
        printf("%5.0f     %8d %15.4f %15.4f\n", difftime(time( NULL), beginTime), arraySize,
										(end1 - startTime1)/(double)CLOCKS_PER_SEC,
										(end2 - startTime2)/(double)CLOCKS_PER_SEC);

		// Delete each node	
		for(j=0; j<listSize; j++){
			free(root[j]);
		}
		free(root); // Delete all pointers to node

	}

  return 0;
}

