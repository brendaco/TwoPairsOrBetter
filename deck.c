#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "deck.h"

#define _CRT_SECURE_NO_WARNINGS
#define SPADE "\u2660" //ASCII art definitions
#define DIAMOND "\u2666"
#define HEART "\u2665"
#define CLUB "\u2663"
#define SQUARE "\u25A0"

// Creates a deck of 52 card
void createDeck(card **head, card **tail) {
  for(int i = 1; i <= 13; i++) { //used to make sure all the faces are created
    addCard(head, tail, i, 's');//creates a card with spades
    addCard(head, tail, i, 'd');//creates a card with diamonds
    addCard(head, tail, i, 'h');//creates a card with hearts
    addCard(head, tail, i, 'c');//creates a card with clubs
  }
  (*tail)->next = NULL; //makes sure last pointer points to NULL
}

// Adds an individual card to the deck
void addCard(card **head, card **tail, int face, char suit) {
  card *temp = (card*)malloc(sizeof(card)); // Allocates the card
  temp->face = face; // Assigns the face to card
  strncpy(&temp->suit, &suit, sizeof(temp->suit)); // Assigns the suit to the card
    
  if (*head == NULL) { // Checks if it is the first card
    *head = temp;
    *tail = temp;
  }
  else { //Adds value to the end of list if not the first card
    (*tail)->next = temp;
    *tail = temp;
  }
}

//Function that prints deck art
void printDeckArt(card *curr) {
  card *currt = curr;//used to print fourth line
  for(int i = 0; i < 5; i++){//prints first line
    for(int j = 0; j < 9; j++) printf("-");
    if(i < 4) printf("  "); //makes sure no more spaces are printed after last card
  }
  
  printf("\n");
  
  while(curr != NULL) {//prints second line using the card values
    printf("|");
    printDeck(curr); //print curr card
    if (curr->face == 10){ //if 10, remover a char since its longer
      for(int i = 0; i < 7; i++){//prints remainder until next card
        if(i == 4) printf("|");
        else printf(" ");
      }
    }
    else{ //prints remainder until next card
      for(int i = 0; i < 8; i++){
        if(i == 5) printf("|");
        else printf(" ");
      }
    }
    curr = curr->next; //goes to the next card
  }

  printf("\n");

  for(int i = 0; i < 5; i++){ //prints third line
    printf("|");
    for(int i = 0; i < 7; i++) printf(" ");
    printf("|");
    printf("  ");
  }
  
  printf("\n");
  
  while(currt != NULL) {//prints fourth line with card values
    printf("|");
    if (currt->face == 10){//if 10, remover a char since its longer
      printf("    ");
      printDeck(currt);
      printf("|");
      printf("  ");
    }
    else{
      printf("     ");
      printDeck(currt);
      printf("|");
      printf("  ");
    }
    currt = currt->next; //goes to the next card 
  }
    
  printf("\n");
    
  for(int i = 0; i < 5; i++){ //print last line
    for(int j = 0; j < 9; j++) printf("-");
    if(i < 4) printf("  ");
  }
  printf("\n\n");
}

// Function that prints card on deck
void printDeck(card *curr) {
  if((curr->face) == 1) printf("A"); //prints the correct face type according to num of face
  else if ((curr->face) == 11) printf("J");
  else if ((curr->face) == 12) printf("Q");
  else if ((curr->face) == 13) printf("K");
  else printf("%d", curr->face);
        
  if ((curr->suit) == 's') printf("%s", SPADE); //prints the suit using ASCII characters
  else if ((curr->suit) == 'd') printf("%s", DIAMOND);
  else if ((curr->suit) == 'h') printf("%s", HEART);
  else printf("%s", CLUB);
}

//Function that shuffles deck (modified from pseudo given on Piazza)
void shuffleDeck(card *head){
  card *pt1;
  card *pt2;
  int k;

  srand((unsigned int)time(0)); //ensures the deck is shuffled after each run

  for(int i = 0; i < 10000; i++){
    pt1 = head;
    for(int j = 0; j < 52; j++){  //loops 52 times for the number of cards in a deck
      pt2 = head;   
            
      k = (rand() % (51 - 0 + 1)) + 0; //assigns k with a random number from 0-51
            
      for(int l = 0; l < k; l++){ //finds the value on k spot
        pt2 = pt2->next;
      }
            
      card *temp = (card*)malloc(sizeof(card));

      temp->face = pt1->face; //swaps the content
      temp->suit = pt1->suit;
      pt1->face = pt2->face;
      pt1->suit = pt2->suit;
      pt2->face = temp->face;
      pt2->suit = temp->suit;

      pt1 = pt1->next; //goes to the next card
    }
  }
}

//Prints an especific line of art
void printArt(int type, char style, char text[50]){ 
  if (type == 1){ //full line of char
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 9; j++) printf("%c", style);
      printf(" ");
    }
  }
  else if(type == 2){ //only center
    for(int i = 0; i < 5; i++){
      if ((i == 0) || (i == 4)){
        for(int j = 0; j < 9; j++) printf(" ");
      }
      else{
        for(int j = 0; j < 9; j++) printf("%c", style);
      }
      printf(" ");
    }
  }
  else{ //text in the middle
    for(int j = 0; j < 9; j++) printf("%c", style);
    printf(" %-30s", text);
    for(int j = 0; j < 9; j++) printf("%c", style);
  }
  printf("\n");
}

//Prints pay
void printPay(){
  printf("\n\n%-40cPay\n", ' ');
  printf("%-17s%s%s %s%s %s%s %s%s %s%-11s%s\n", "Royal Flush", "10", SPADE, "J", SPADE, "Q", SPADE, "K", SPADE, "A", SPADE, "250*bet");
  printf("%-17s%s%s %s%s %s%s %s%s %s%-12s%s\n", "Straight Flush", "2", CLUB, "3", CLUB, "4", CLUB, "5", CLUB, "6", CLUB, "100*bet");    printf("%-17s%s%s %s%s %s%s %s%s %-13s%s\n", "Four of a Kind", "9", SPADE, "9", CLUB, "9", DIAMOND, "9", HEART, SQUARE, "50*bet");
  printf("%-17s%s%s %s%s %s%s %s%s %s%-12s%s\n", "Full House", "9", DIAMOND, "9", HEART, "9", SPADE, "3", CLUB, "3", HEART, "25*bet");
  printf("%-17s%s%s %s%s %s%s %s%s %s%-12s%s\n", "Flush", SQUARE, CLUB, SQUARE, CLUB, SQUARE, CLUB, SQUARE, CLUB, SQUARE, CLUB, "10*bet");
  printf("%-17s%s%s %s%s %s%s %s%s %s%-12s%s\n", "Straight", "4", SQUARE, "5", SQUARE, "6", SQUARE, "7", SQUARE, "8", SQUARE, "5*bet");
  printf("%-17s%s%s %s%s %s%s %s %-14s%s\n", "Three of a Kind", "9", SPADE, "9", CLUB, "9", DIAMOND, SQUARE, SQUARE, "4*bet");
  printf("%-17s%s%s %s%s %s%s %s%s %-13s%s\n", "Two Pairs", "K", SPADE, "K", DIAMOND, "6", DIAMOND, "6", HEART, SQUARE, "2*bet");
}

//analyzes the hand
int analyzeHand(card *handh){ 
  card *temp = handh;
  int value = 0; //used to calculate highest possible value of card
  int face[5], tempf, i, j, k;
  char suit[5], temps;
  for(i = 0; i < 5; i++){ //transfers values of face and suits into array for an easier process
    face[i] = temp->face;
    suit[i] = temp->suit;
    temp = temp->next;
  }
  for(j = 0; j < 5; ++j){ //arranges cards in ascending order
    for(k = j + 1; k < 5; ++k){
      if (face[j] > face[k]){
        tempf = face[j];
        temps = suit[j];
        face[j] = face[k];
        suit[j] = suit[k];
        face[k] = tempf;
        suit[k] = temps;
      }
    }
  }
  
  if((suit[0] == suit[1]) && (suit[0] == suit[2]) && (suit[0] == suit[3]) && (suit[0] == suit[4])){
    value = 4; //hand is at least a flush
    if((face[0] == face[1] - 1) && (face[1] == face[2] - 1) && (face[2] == face[3] - 1) && (face[3] == face[4] - 1)){
        value = 7;//hand is at least a straight flush
    }
    if ((face[0] == 1) && (face[1] == 10)) value = 8;//hand is a royal flush
  }
  else if((face[0] == face[1] - 1) && (face[1] == face[2] - 1) && (face[2] == face[3] - 1) && (face[3] == face[4] - 1)){
    value = 3; //value is a straight hand and cant be a flush
  }
  else if((face[1] == face[2] - 1) && (face[2] == face[3] - 1) && (face[3] == face[4] - 1) && (face[0] == 1) && (face[1] == 10)){
    value = 3; //value is a straight hand(10-A)and cant be a flush
  }
  else if((face[0] == face[2]) || (face[1] == face[3]) || (face[2] == face[4])){
    value = 2; //value is at least a three of a kind
    if((face[0] == face[3]) || (face[1] == face[4])) {
      value = 6; //value is a four of a kind
    }
    else if((face[0] == face[2]) && (face[3] == face[4])){
        value = 5; //value is a full house
    }
    else if((face[2] == face[4]) && (face[0] == face[1])){
        value = 5; //value is a full house
    }
  }
  else if(((face[0] == face[1]) && (face[2] == face[3])) || ((face[0] == face[1]) && (face[3] == face[4])) || ((face[1] == face[2]) && (face[3] == face[4]))){ 
    value = 1; //value is two pairs
  }
  //0 = nothing
  //1 = Two Pair 
  //2 = Three of a Kind
  //3 = Straight
  //4 = Flush
  //5 = Full House  
  //6 = Four of a Kind 
  //7 = Straight Flush
  //8 = Royal Flush
  return value;
}

//updates hand
void update(card **handh, card **head, card **handt, int keep[5]){
  card *temp = *handh;
  card *currh = NULL;
  card *currt = NULL;
  for(int i = 0; i < 5; i++){ //checks all 5 cards in hand
    if(keep[i] == 0){ //if card will be replaced
      addCard(&currh, &currt, (*head)->face, (*head)->suit); //adds card from deck into hand
      *head = (*head)->next; //removes card from deck
      currt->next = NULL;
      temp = temp->next; //removes card from prev hand to keep order
    }
    else if(keep[i] == 1){ //if card is hold
      addCard(&currh, &currt, temp->face, temp->suit); //adds card from prev hand into new hand
      temp = temp->next; //removes card from prev hand
      currt->next = NULL;
    }
  }
  *handh = currh;//returns new values into hand
  *handt = currt;
} 