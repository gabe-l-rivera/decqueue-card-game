/*
 File Name: doublyLinkedList.h
 Course: CS315 Project 1: "Deck of Dequeues"
 Author: Created by Gabe Rivera on 1/26/20.
 Purpose: Header file (.h) containing the prototypes of doubly linked list fucntions and node structure declatation
 */


#ifndef doublyLinkedList_h
#define doublyLinkedList_h
#include <stdbool.h>
#include <stdio.h>

struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
};

void dieRollChecker(int nSidedRollFirst, int nSidedRollSecond, int twoSidedRoll, int numberOfPlayers);
void argChecker(int numberOfPlayers,int numberOfCards,int turns);
bool playRound(struct Node** advantagePile, struct Node** disadvantagePile, int twoSiidedRoll, int nSidedDieRollFirst, int nSidedDieRollSecond);
bool zeroWeight(struct Node** advantagePile);
int winningPile(int *array, int size);
void displayWeight(struct Node ** pile);
int getWeight(struct Node **pile);
int getSize(struct Node **pile);
int getHeadValue(struct Node **pile);
int getLastNodeValue(struct Node **pile);
void dealCards(struct Node** pile, int numCards);
void displayPile(struct Node* node);
void removeFromPile(struct Node** head, struct Node* nodeToDelete);
void removeKthNodeFromEnd(struct Node** head, int k);
void insertFront(struct Node** head, int data);

#endif /* doublyLinkedList_h */

