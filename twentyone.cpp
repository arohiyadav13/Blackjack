/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
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
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for(int i = 51; i>=1; i--)
  {
    int j = (rand() % (i+1));
    int temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }


}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/

  //value 

  int modVal = id%13;
  if(modVal<9)
  {
    int value = 2 + modVal;
    cout << value << "-";
  }
  else if(modVal == 9)
  {
    cout << "J" << "-";
  }
  else if(modVal == 10)
  {
    cout << "Q" << "-";
  }
  else if(modVal == 11)
  {
    cout << "K" << "-";
  }
  else
  {
    cout << "A" << "-";
  }
  
  
  
  //suit 
  if(id/13 == 0)
  {
    cout << "H";
  }
  if(id/13 == 1)
  {
    cout << "S";
  }
  if(id/13 == 2)
  {
    cout << "D";
  }
  if(id/13 == 3)
  {
    cout << "C";
  }
  
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  //find card value
  int index = id%13;
  int val = value[index];
  return val;


}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/

  for(int i = 0; i< numCards; i++)
  {
    printCard(hand[i]);
    cout << " ";
  }

  cout<< endl;



}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/

  int totalScore = 0;
  int numAces = 0;

  for(int i = 0; i<numCards; i++)
  {
    totalScore+=cardValue(hand[i]);
    if(cardValue(hand[i]) == 11)
    {
      numAces++;
    }
  }

  while(totalScore>21 && numAces>=1)
  {
    totalScore-=10;//adjusts score if over 21
    numAces--; 
  }

  return totalScore;
  




}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/

  bool playAgain = true;

  while(playAgain)
  { 
    for(int i = 0; i< NUM_CARDS; i++)
    {
      cards[i] = i;
    }

    shuffle(cards);

    int playerCards = 2;
    int dealerCards = 2;

    //assigns cards
    phand[0] = cards[0];
    dhand[0] = cards[1];
    phand[1] = cards[2];
    dhand[1] = cards[3];

    while(true)
    {
      //print dealer and player hands
      cout << "Dealer: ? ";
      printCard(dhand[1]);
      cout << endl;
      cout << "Player: ";
      printHand(phand, playerCards);


      //hit or stay options when score is <21
      while(getBestScore(phand, playerCards)<21)
      {
        char choice;
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        cin >> choice;

        if(choice == 'h')
        {
          phand[playerCards] = cards[playerCards+2];
          playerCards++;
          cout << "Player: ";
          printHand(phand, playerCards);
        }
        else
        {
          break;
        }

      }
      //the following accounts for each case
      if(getBestScore(phand, playerCards)>21)
      {
        cout << "Player busts" << endl;
        //int p = getBestScore(phand, playerCards);
        //int d = getBestScore(dhand, dealerCards);
        cout << "Lose " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
        break;
      }

      if(getBestScore(phand, playerCards)<=21)
      {
        //printHand(dhand, dealerCards);
        
        while(getBestScore(dhand, dealerCards)<17)
        {
          dhand[dealerCards] = cards[dealerCards+playerCards];
          dealerCards++;
        }
      }
        
        cout << "Dealer: ";
        printHand(dhand, dealerCards);

        if(getBestScore(dhand, dealerCards) > 21)
        {
          cout << "Dealer busts" << endl;
          cout << "Win " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
          break;
        }

        if(getBestScore(phand, playerCards) == getBestScore(dhand, dealerCards))
        {
          //int p = getBestScore(phand, playerCards);
          //int d = getBestScore(dhand, dealerCards);
          cout << "Tie " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
          break;
        }
        // if((getBestScore(phand, playerCards) == 21) && (getBestScore(dhand, dealerCards) != 21))
        // {
        //   //int p = getBestScore(phand, playerCards);
        //   //int d = getBestScore(dhand, dealerCards);
        //   cout << "Win " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
        //   break;
        // }
        if(getBestScore(phand, playerCards) < getBestScore(dhand, dealerCards))
        {
          cout << "Lose " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
          break;
        }
        else
        {
          cout << "Win " << getBestScore(phand, playerCards) << " " << getBestScore(dhand, dealerCards) << endl;
          break;
        }

      }


      char again;
      cout << "Play again? [y/n]" << endl;
      cin >> again; 

      if(again == 'y')
      {
        playAgain = true;
      }
      else
      {
        playAgain = false;
        break;
      }

    
    
  }
  return 0;
}
