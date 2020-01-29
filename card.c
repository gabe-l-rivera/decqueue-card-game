/*
 File Name: cards.c
 Course: CS315 Project 1: "Deck of Dequeues"
 Author: Created by Gabe Rivera on 1/26/20.
 Purpose: .c file containing the implementation doubly linked list functions and main method
 
*/

#include "doublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


void insertFront(struct Node** head, int data){
    // Parameters: reference(&) to head, and int data
    // Return: void, mutates the list by adding node to front
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));  // create new node
    newNode->data = data;  // set data
    newNode->next = (*head); // set next pointer to point to head
    newNode->prev = NULL; // set prev pointer to point to NULL
    
    if ((*head) != NULL)    // change prev pointer of head node to new node
        (*head)->prev = newNode;
    (*head) = newNode; // set the head to point to the new node
}

void removeKthNodeFromEnd(struct Node** head, int k){
    // Parameters: reference(&) to head and int k representing a postion to delete from
    // Return: void, mutates the list by deleting a node    
    int count = 1;
    struct Node *pseudoHead = *head;
    struct Node *firstNode = *head;
    struct Node *secondNode = *head;
    
    while(count <= k){
        secondNode = secondNode->next;
        count += 1;
    }
    
    if(secondNode == NULL){
        pseudoHead->data = pseudoHead->next->data;
        pseudoHead->next = pseudoHead->next->next;
    }
    
    while(secondNode->next != NULL){
        secondNode = secondNode->next;
        firstNode = firstNode->next;
    }
    firstNode->next = firstNode->next->next;
}

void removeFromPile(struct Node** head, struct Node* nodeToDelete){
    // Parameters: reference(&) to head, and node to delete
    // Return: void, mutates the list by deleting the node from the list
    if (*head == NULL || nodeToDelete == NULL)
        return;
    
    if (*head ==nodeToDelete)
        *head = nodeToDelete->next;
    
    if (nodeToDelete->next != NULL)
        nodeToDelete->next->prev = nodeToDelete->prev;
    
    if (nodeToDelete->prev != NULL)
        nodeToDelete->prev->next = nodeToDelete->next;
    
    free(nodeToDelete);
    return;
}


void displayPile(struct Node* node){
    // Parameters: reference to a node
    // Return: void, prints list
    while (node != NULL) {
        printf(" %d ", node->data);
        //last = node;
        node = node->next;
    }
    printf("\n");
    
}

void dealCards(struct Node** pile, int numCards){
    // Parameters: reference to pile and number of cards
    // Return: void, adds cards to pile
    for(int i = numCards; i >= 1; i--)
        insertFront(pile, i);
    
}

int getLastNodeValue(struct Node **pile){
    // Parameters: reference to pile
    // Return: int, last node's data
    struct Node *temp = *pile;
    
    while(temp->next != NULL){
        temp = temp->next;
    }
    return temp->data;
}

int getHeadValue(struct Node **pile){
    // Parameters: reference to a pile
    // Return: int, head value
    struct Node *temp = *pile;  
    while(temp->prev != NULL){
        temp = temp->next;
    }
    return temp->data;
}

int getSize(struct Node **pile){
    // Parameters: reference to a pile
    // Return: int, pile size
    int size = 0;
    struct Node *temp = *pile;
    
    while(temp != NULL){
        size += 1;
        temp = temp->next;
    }
    return size;
}

int getWeight(struct Node **pile){
    // Parameters: reference to a pile
    // Return: int, pile's weight
    struct Node *temp = *pile;
    int value; 
    int weight = 0, depth = 1;
    // 1*1 + 2*2 + ... + c*c = c(c+1)(2c+1)/6
    while(temp != NULL){
        value = temp->data;
	weight = weight + (depth * value);
	depth += 1;
	temp = temp->next;
    	//weight = ((size)*(size + 1)*(2*size + 1))/6;    // is this the correct implementation?
    }
    return weight;
}

void displayWeight(struct Node ** pile){
    // Parameters: reference to a pile
    // Return: void, prints weight of pile  
    int weight = getWeight(pile);
    printf("%d\n", weight);
}

int winningPile(int *array, int size){
    // Parameters: reference to array
    // Return: int, index of lowest weight pile
	int min = array[1]; // set minimum value to array[1]
	int returnIndex = 1; // index to return, rep. the lowest index
	for(int i = 2; i <= size; i++){
		if(min >= array[i]){
			min = array[i];
			returnIndex = i;
		}
	}
	return returnIndex;
}

bool zeroWeight(struct Node** advantagePile){
    // Parameters: reference to a pile
    // Return: bool, if pile is empty-> true, otherwise false
	if(getWeight(advantagePile) == 0)
		return true;
	return false;
}

bool playRound(struct Node** advantagePile, struct Node** disadvantagePile, int twoSiidedRoll, int nSidedDieRollFirst, int nSidedDieRollSecond){
    // Parameters: reference to a advantagePile & disadvantagePile and three die roll values (twoSiidedRoll,nSidedDieRollFirst and nSidedDieRollSecond)
    // Return: bool, false if weight is zero and true otherwise
     struct Node *tempHead = *advantagePile;
     if(tempHead->next == NULL){
	 removeFromPile(advantagePile, tempHead);
         printf("GAME IS OVER; Player %d has 0 cards remaining and won the game!\n", nSidedDieRollFirst);
	 return false;
    }
	
   // Debug: printf("Player with advantage: Player %d.\n\n", nSidedDieRollFirst);
   // Debug: printf("Player to accept the discarded card: Player %d.\n\n", nSidedDieRollSecond);
   // Debug: printf("Player %d sends card a card to player %d for the top of the pile:",nSidedDieRollFirst, nSidedDieRollSecond);
    if(twoSiidedRoll == 1){ // remove from top
	 //Debug: printf("Player %d sends card a card to player %d for the top of the pile:",nSidedDieRollFirst, nSidedDieRollSecond);
        if(getWeight(disadvantagePile) > 0){
            //Dubug: printf("Tossing 2-sided die... Player %d rolled a 1! Player %d will discard from top.\n\n", nSidedDieRollFirst, nSidedDieRollFirst);
            printf("Player %d sends a card to player %d from the top of the pile:\n", nSidedDieRollFirst, nSidedDieRollSecond);
	    insertFront(disadvantagePile, getHeadValue(&tempHead));
	    removeFromPile(advantagePile, tempHead); // remove node from head (top)
	    return true;
        }
    }
    else if (twoSiidedRoll == 2){
        if(getWeight(disadvantagePile) > 0){
            printf("Player %d sends a card to player %d from the bottom of the pile:\n",nSidedDieRollFirst, nSidedDieRollSecond);    
	    insertFront(disadvantagePile, getLastNodeValue(&tempHead));
	    removeKthNodeFromEnd(advantagePile,1); // remove node from tail (bottom)         
            return true;
        }
    } else {
        printf("Invalid dice roll.\n");
    }
    
    printf("\n\n");
    return false;
}

void argChecker(int numberOfPlayers,int numberOfCards,int turns){ // Checks args for reasonable values
	if(numberOfPlayers <= 0 || numberOfPlayers > INT_MAX){
		printf("Please enter a resonable amount of players.\n");
		exit(1);
	}	
	if(numberOfCards <= 0 || numberOfCards > INT_MAX){
		printf("Please enter a resonable amount of cards.\n");
                exit(1);
	}
	if(turns <= 0 || turns > INT_MAX){
		printf("Please enter a resonable amount of turns.\n");
                exit(1);
	}
}

void dieRollChecker(int nSidedRollFirst, int nSidedRollSecond, int twoSidedRoll, int numberOfPlayers){ // Checks args for reasonable values
	if(nSidedRollFirst > INT_MAX || nSidedRollFirst <  INT_MIN){
		printf("Error in dice roll. Please try again.\n");
		exit(1);
	}
	if(nSidedRollSecond > INT_MAX || nSidedRollSecond < INT_MIN){
		printf("Error in dice roll. Please try again.\n");
                exit(1);
	}
	if(twoSidedRoll > 2 || twoSidedRoll < 1){
		printf("Error in dice roll. Please try again.\n");
                exit(1);
	}
}


int main(int argc, char *argv[]){

    int numberOfPlayers = atoi(argv[1]);
    int numberOfCards = atoi(argv[2]);
    int turns = atoi(argv[3]);
    argChecker(numberOfPlayers,numberOfCards,turns);
    struct Node *pile[numberOfPlayers];    // create a list of structures 0 to numberOfPlayers;

    for(int i = 1; i <= numberOfPlayers; i++){   // set all stucts to NULL and add cards
        pile[i] = NULL;
        dealCards(&pile[i], numberOfCards);
    }
    printf("---------- INITIAL PILES ----------\n");
    for(int i = 1; i <= numberOfPlayers; i++){   // display cards
        printf("\n ---------------- \n Player Pile %d:\n ---------------- \n", i);
        displayPile(pile[i]);
    }
    printf("\n");

    int nSidedRollFirst;
    int nSidedRollSecond;
    int twoSidedRoll;
    bool play = true;
    int weightArray[numberOfPlayers];
    int i = 1;

    while(turns > 0 && play){
	scanf("%d",&nSidedRollFirst);
        scanf("%d",&twoSidedRoll);
	scanf("%d",&nSidedRollSecond);
	nSidedRollFirst = (nSidedRollFirst % numberOfPlayers)+1;
	nSidedRollSecond = (nSidedRollSecond % numberOfPlayers)+1;
	twoSidedRoll = (twoSidedRoll % 2) + 1;
	dieRollChecker(nSidedRollFirst,nSidedRollSecond,twoSidedRoll,numberOfPlayers);
        printf("Turn %d: ", i);
	play = playRound(&pile[nSidedRollFirst], &pile[nSidedRollSecond], twoSidedRoll, nSidedRollFirst, nSidedRollSecond);
        turns -=1;
	i += 1;

	for(int i = 1; i <= numberOfPlayers; i++){
		weightArray[i] = getWeight(&pile[i]);
		printf("\tPlayer %d weight: %d\n", i, getWeight(&pile[i]));
	}

	printf("\n");
   	
	if(turns == 0){
   	     printf("\tNo more rounds. Player %d wins.\n\n", winningPile(weightArray, numberOfPlayers));
    	}
		
    }

    printf("---------- FINAL PILES ----------\n");
    for(int i = 1; i <= numberOfPlayers; i++){   // display cards
        printf("\n ---------------- \n Player Pile %d:\n ---------------- \n", i);
        displayPile(pile[i]);
    }
    printf("\n");
 
    return 0;
}

