/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Initialized the deck then 
 * shuffles the deck using the Fisher-Yates / Durstenfeld shuffle algorithm
 
 */
void shuffle(int cards[]) {
  for (int i = 0; i < NUM_CARDS; i++) {
    cards[i] = i;
  }

  for (int a = (NUM_CARDS - 1); a > 0; a--) {
    int b = rand() % (a + 1);
    int c = cards[a];
    cards[a] = cards[b];
    cards[b] = c;
  }

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 */
void printCard(int id) {
  cout << type[id % 13] << "-" << suit[id / 13];

  /******** You complete ****************/
}

/**
 * Returns the numeric value of the card.
 */
int cardValue(int id) {
  /******** You complete ****************/
  return value[id % 13];

}

/**
 *Prints out each card in the hand separated by a space and
 * then print a newline at the end.
 */
void printHand(int hand[], int numCards) {
  for (int u = 0; u < numCards; u++) {
    printCard(hand[u]);
    cout << " ";
  }
  cout << endl;

}

/**
  Returns the total score of the provided hand.  
 */
int getBestScore(int hand[], int numCards) {
  int p = 0;
  int ace = 0;
  for (int t = 0; t < numCards; t++) {
    if (value[hand[t] % 13] == 11) {
      ace++;
      if ((p + 11) != 21) {
        p += 11;
      }
      if ((p + 11) == 21) {
        p += 11;
      }

    } else {
      p += value[hand[t] % 13];
    }

  }

  if ((p > 21) && (ace > 0)) {
    p = p - 10;
    ace = ace - 1;
  }
  return p;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];

bool playbool = true;
  bool lose = false;
  char play;
  char choice = 's';
  int hitp = 1;
  int hitd = 1;
  int sizep = 2;
  int sized = 2;
  int deck = 4;

// starts code if player chooses to play again. Will start automatically for first iteration
  while (playbool == true) {
    hitp = 1;
    hitd = 1;
    sizep = 2;
    sized = 2;
    deck = 4;

    shuffle(cards);
    dhand[0] = cards[1];
    dhand[1] = cards[3];
    phand[0] = cards[0];
    phand[1] = cards[2];

// Dialouge to start a round

    cout << "Dealer: " << "? ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand, sizep);
    
// Checks to make sure that the player didn't have 21 from the initial cards dealt.
    if ((getBestScore(phand, sizep)) != 21) {
      cout << "Type 'h' to hit and 's' to stay: " << endl;
      cin >> choice;
    }

// Code to ask player if they want to stay or hit

    while (choice == 'h') {
      phand[1 + hitp] = cards[deck];
      hitp++;
      deck++;
      sizep++;

      cout << "Player: ";
      printHand(phand, sizep);
      if ((getBestScore(phand, sizep)) > 21) {
        cout << "Player busts " << endl;
        cout << "Lose " << getBestScore(phand, sizep) << " " << getBestScore(dhand, sized) << endl;
        lose = true;
        break;

      } else if (((getBestScore(phand, sizep))) == 21) {
        break;

      } else {
        cout << "Type 'h' to hit and 's' to stay: " << endl;
        cin >> choice;
      }

    }
    
// Code to make sure that dealer's hand is at least 17
    while (getBestScore(dhand, sized) < 17) {
      dhand[1 + hitd] = cards[deck];
      hitd++;
      deck++;
      sized++;
    }

// Code that computes who has the closest score to 21 and determines who wins

    if (lose == false) {
      if (getBestScore(dhand, sized) > 21) {
        cout << "Dealer: ";
        printHand(dhand, sized);
        cout << "Dealer busts" << endl;
        cout << "Win " << getBestScore(phand, sizep) << " " << getBestScore(dhand, sized) << endl;
      } else if ((21 - getBestScore(phand, sizep)) > (21 - getBestScore(dhand, sized))) {
        cout << "Dealer: ";
        printHand(dhand, sized);
        cout << endl;
        cout << "Lose " << getBestScore(phand, sizep) << " " << getBestScore(dhand, sized) << endl;
      } else if ((21 - getBestScore(phand, sizep)) < (21 - getBestScore(dhand, sized))) {
        cout << "Dealer: ";
        printHand(dhand, sized);
        cout << "Win " << getBestScore(phand, sizep) << " " << getBestScore(dhand, sized) << endl;

      } else if ((21 - getBestScore(phand, sizep)) == (21 - getBestScore(dhand, sized))) {
        cout << "Dealer: ";
        printHand(dhand, sized);
        cout << "Tie " << getBestScore(phand, sizep) << " " << getBestScore(dhand, sized) << endl;
      }
    }

// Asks player if they want to play again

    cout << endl;
    cout << "Play Again? [y/n]" << endl;
    cin >> play;
    if (play == 'y') {
      playbool = true;

    } else {
      playbool = false;
    }
  }
  return 0;
}