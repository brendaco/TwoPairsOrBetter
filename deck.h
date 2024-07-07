
typedef struct card_s {// Given struct
  char suit;
  int face;
  struct card_s *next;
} card;

void createDeck(card **head, card **tail); // Creates a deck of 52 card
void addCard(card **head, card **tail, int face, char suit); // Adds an individual card to the deck
void printDeckArt(card *curr); //Function that prints deck art
void printDeck(card *curr); // Function that prints card on deck
void shuffleDeck(card *head); //Function that shuffles deck (modified from pseudo given on Piazza)
void printArt(int type, char style, char text[50]); //Prints an especific line of art
void printPay(void); //Prints pay
int analyzeHand(card *handh); //analyzes the hand
void update(card **handh, card **head, card **handt, int keep[5]); //updates hand
