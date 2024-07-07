/*
main.c
(deck.c, deck.h)

Final - Two Pairs or Better

Brenda Coutino
ECE 175
12/06/2021
 */

#define _CRT_SECURE_NO_WARNINGS

#include "deck.h" //contains functions created for the game
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPADE "\u2660" // ASCII art definitions
#define DIAMOND "\u2666"
#define HEART "\u2665"
#define CLUB "\u2663"
#define SQUARE "\u25A0"

int main(void) {
	card *head = NULL;  // head of deck
	card *tail = NULL;  // tail of deck
	card *handh = NULL; // head of player's hand
	card *handt = NULL; // tail of player's hand

	card *temp =
		(card *)malloc(sizeof(card)); // used to count num of cards in deck
	char name[50];					  // name of player
	char temptext[50]; // used for printing num of coins with name
	int coins = 100;   // coins of player, starts at 100 coins
	int bet = 0;	   // amount of bet placed by player
	int choice;		   // used when asking for cards to hold
	int value;		   // used to analyze value of hand

	printf("Enter your name:");
	fgets(name, 50, stdin);
	name[strlen(name) - 1] = '\0'; // makes sure last char in name is not \n

	printArt(1, '$', "no"); // prints art
	printArt(2, '$', "no");
	printf("%s,\n\tLet's play Two pairs or Better\n", name);
	printArt(2, '$', "no");
	printArt(1, '$', "no");
	printArt(3, '$', "Rank of winning");

	printPay(); // prints Pay
	printf("\n\n");

	createDeck(&head, &tail); // Calls to create deck
	shuffleDeck(head);		  // Shuffles deck

	// LOOP OF GAME STARTS
	while (1 == 1) { // loops until -1 is betted or player runs out of coins

		printArt(1, '*', "no");
		char temptext[50],
			append[50]; // used to print name with current num of coins
		strcpy(temptext, name);
		strcat(temptext, " you have ");
		sprintf(append, "%d", coins);
		strcat(temptext, append);
		strcat(temptext, " coins");
		printArt(3, '*', temptext);
		printArt(1, '*', "no");

		while ((bet < 1) ||
			   (bet > coins)) { // Loop until a proper bet is inputted
			printf(
				"\nPlace your bet (1-%d) coins (-1 to quit playing):\n", coins);
			scanf("%d", &bet);

			if (bet == -1)
				break; // ends loop if -1 is entered
		}

		if (bet == -1)
			break; // quits the game if user bets -1

		printf("You bet %d coins\n", bet);

		printf("%s's hand;\n", name);

		for (int i = 0; i < 5; i++) { // adds 5 cards to players hand
			addCard(
				&handh,
				&handt,
				head->face,
				head->suit);   // adds card from deck into hand
			head = head->next; // removes card from deck
			handt->next = NULL;
		}
		printDeckArt(handh); // prints hand

		choice = 0;
		int keep[5] = {0, 0, 0, 0, 0}; // used to find which cards to keep
		int num = 0;				   // used to check for kept cards
		while (1 == 1) {
			printf("Pick cards (between 1-5) to hold (-1 to stop):\n");
			scanf("%d", &choice);
			if (choice == -1)
				break; // breaks if user stops

			else if ((choice >= 1) && (choice <= 5)) { // says which card to
													   // keep
				keep[choice - 1] = 1;
			}
			for (int i = 0; i < 5; i++) { // used to check if user kept all
										  // cards
				if (keep[i] == 1)
					num++;
			}
			if (num == 5)
				break; // breaks if all cards were kept
			num = 0;
		}

		update(&handh, &head, &handt, keep); // updates hand
		printDeckArt(handh);

		value = analyzeHand(handh); // analyzes value of hand

		if (value == 0) { // if hand has no more than two pairs
			coins -= bet;
			printf("You LOST and you now have %d coins\n", coins);
		} else if (value == 1) { // two pairs win
			coins += (bet * 2);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 2),
				coins);
		} else if (value == 2) { // three of a kind win
			coins += (bet * 4);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 4),
				coins);
		} else if (value == 3) { // straight win
			coins += (bet * 5);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 5),
				coins);
		} else if (value == 4) { // flush win
			coins += (bet * 10);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 10),
				coins);
		} else if (value == 5) { // full house win
			coins += (bet * 25);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 25),
				coins);
		} else if (value == 6) { // four of a kind win
			coins += (bet * 50);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 50),
				coins);
		} else if (value == 7) { // straight flush win
			coins += (bet * 100);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 100),
				coins);
		} else if (value == 8) { // royal flush win
			coins += (bet * 250);
			printf(
				"You WON %d coins and you now have %d coins\n",
				(bet * 250),
				coins);
		}

		int count = 0; // used to cound num of cards left
		temp = head;

		while (temp != NULL) { // counts number of cards left
			temp = temp->next;
			count++;
		}

		free(temp);

		if (count < 20) { // creates new deck if there's less than 20 cards
			free(head);   // frees current deck of cards
			createDeck(&head, &tail); // Calls to recreate deck
			shuffleDeck(head);		  // Shuffles deck
		}

		free(handh); // resets hand for next round
		bet = 0;	 // resets bet

		if (coins <= 0) { // checks if no coins left
			printf("You lost all your coins. Game Over!\n");
			break; // ends game if no coins left
		}

		char ans;		 // used to check if user wants to continue playing
		ans = getchar(); // reads a dummy character to clear

		printf("Hit Enter key to continue:\n");
		ans = fgetc(stdin);

		if (ans != 10)
			break; // quits if user does not press enter key
	}

	printf("Goodbye %s\n", name);
	free(head); // frees deck
	return 0;
}