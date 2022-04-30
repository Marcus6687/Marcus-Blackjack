#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;


int getRandomNumber(int low, int high);
int CardValue(int card);
int getTopCard(int deck[]); 
int getHandValue(const int hand[]); 
bool playAnotherHand(char&);
bool userWantsToDraw(char&); 
void initializeDeck(int deck[]); 
void dumpDeck(int deck[], int size); 
void shuffle(int deck[], int size); 
void ShowCard(int card); 
void showCards(const int cards[], int numCards, bool hideFirstCard); 
void whoWins(const int pH[], const int dH[]); 
void checkBust(const int pH[], const int dH[], char Play); 
void blackJack(const int pH[], const int dH[], char Play); 
void naturalBlackJack(const int pH[], const int dH[], char Play);
void playOneHand(); 
void scoreBoard(const int pH[], const int dH[]); 
void backdoorKenny(const int hand[]); 
void checkSoftOrHard(int pH[]); 
void softOrHardAI(int dH[], int pH[]); 
void Difficulty(); 
void Rules(); 
void addToHand(int hand[], int cardToAdd); 
void hitUntilStand(int dH[], int deck[], int pH[]); 


int topCard = 0;
float win = 1.00;
int level;
int main() {

Rules();
Difficulty();
playOneHand();
return 1;
}

void Rules()
{
cout<<"Welcome to Blackjack"<<endl;
cout<<"Here are the rules"<<endl;
cout<<"1 Aces can be either one or 11 points"<<endl;
cout<<"2 dealer wins ties unless player has a blackjack"<<endl;
cout<<"Winning conditions are:"<<endl;
cout<<"Your score beats dealers score"<<endl;
cout<<"If your score is higher than dealers"<<endl;


}


void Difficulty()
{
cout<<"\n";
cout<<"choice difficulty (1) beginner, (2) expert.";
cin >> level;
cout<<"\n";

if(level != 1)
{
    if(level != 2)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "enter level of difficulty 1 or 2 pls"<<endl;
                Difficulty();
   }


}


}

void playOnrHand()
{

char Play = 'N'; 
do {
char Draw = 'H';
int deck[52];
initializeDeck(deck);
shuffle(deck, 51);
int pH[10] = {0};
int dH[10] = {0};
addToHand(pH, getTopCard(deck));
addToHand(dH, getTopCard(deck));
addToHand(pH, getTopCard(deck));
addToHand(dH, getTopCard(deck));
cout<<"***************************"<<endl;
cout<<"\n"<<endl;
cout<< "The Dealer shuffled and dealt you each your cards.";
cout<< "\n"<<endl;
naturalBlackJack(pH, dH, 'y');
blackJack(pH, dH, 'y');
cout<<"your hand:" <<endl;
showCards(pH, 10, true);
cout<< "\n\nDealer Hand:" << endl;
showCards(dH, 10, true);
checkSoftOrHard(pH);

while (userWantsToDraw(Draw))

{
addToHand(pH, getTopCard(deck));
cout << "The dealer dealth you another.\n"<<endl;
cout<<" your hand:"<< endl;
showCards(pH, 10, false);
checkSoftOrHard(pH);
checkBust(pH, dH, 'y');
blackJack(pH, dH, 'y');
    /* code */
}

hitUntilStand(dH, deck, pH);
cout<< endl;
checkBust(pH, dH, 'y');
blackJack(pH, dH, 'y');
whoWins(pH, dH);
cout << endl;
cout << "winnings multiplier: " << win << endl;
}
while (playAnotherHand(Play));

}

void initilizeDeck(int deck[])
{
 int Rank = 101;
 int i = 0;
 for(i = 0 ; i<=13; i++)
{
    //Hearts 
 deck[i] = Rank++;
}

for(i = 13 ; i<=26; i++)
{
    //Diamond 
 deck[i] = Rank++ + 100 - 14;
}

for(i = 26 ; i<=39; i++)
{
    //Clubs 
 deck[i] = Rank++ + 200 - 28;
}

for(i = 39 ; i<=51; i++)
{
    //Spades
 deck[i] = Rank++ + 300 - 42;
}

}

void shuffle(int deck[], int size)
{
for (int i=0; i<500; i++)
{
    int T1 = 0;
    int R1 = getRandomNumber(0, size);
    int R2 = getRandomNumber(0, size);
    T1 = deck[R1];
    deck[R1] = deck[R2];
    deck[R2] = T1;
    /* code */
}
}

int getTopCard(int deck[])
{
for(int i = 0; i < 51; i++)
{
if(deck[i] != 0)
{
 topCard = deck[i];
 deck[i] = 0;
 return topCard;
}
}
}
void naturalBlackJack(const int pH[], const int dH[], char Play)
{
 int playerScore = getHandValue(pH);
 int dealerScore = getHandValue(dH);
 if((playerScore == 21) && (dealerScore != 21))
{
scoreBoard(pH, dH);
cout << "\n";
cout << "Natural Blackjack! You win a 3:2 payout.";
win = win + 1.5; backdoorKenny(pH);
 playAnotherHand(Play); 

}

}

void blackJack(const int pH[], const int dH[], char Play)
{
 int playerScore = getHandValue(pH);
 int dealerScore = getHandValue(dH);
 if((playerScore == 21) && (dealerScore != 21))
{
 cout << "VIVI";
 scoreBoard(pH, dH);
 cout << "\n"; cout << "Blackjack! You win a 3:2 payout." << endl;
 win = win + 1.5;
 cout << "\n"; cout << "Winnings multiplier: " << win << endl;
 backdoorKenny(pH);
 playAnotherHand(Play);


}
 else if((playerScore == 21) && (dealerScore == 21))
{
 scoreBoard(pH, dH); cout << "\n"; 
 cout<<"Dealer & you got Blakjack. Push in your favor at 1:1 ratio"<<endl;
 win++;
 cout <<"\n"; cout << "Winnings multiplier: " << win << endl;
 playAnotherHand(Play);


}


}

void showCards(const int deck[], int numCards, bool hideFtrstCard)
{
  if(hideFtrstCard)
 {
 cout << "** ";

 }

  else 
  {
 ShowCard(deck[0]);
 cout << "";

  }

  for(int i=1; i<numCards; i++)
{
if(deck[i] != 0)
{
ShowCard(deck[i]);
cout<< "";
}
}
}

void checkSoftOrHard(int pH[])
{
 for(int i=0; i<9; i++)
 {
      int checkAce = CardValue(pH[i]);
      int softOrHard;
if(checkAce ==1 || checkAce == 11)
{
cout<< "\n";
cout<<"\nwould you like your Ace to count as 1 or 11 points? (1/11): ";
cin>> softOrHard;
if(softOrHard == 1)
{
if(checkAce == 11)
pH[i] = pH[i] + 13;
}

else if(softOrHard == 11) 
{

if(checkAce == 1)
{
    pH[i] = pH[i] - 13;
}

}

else if (softOrHard != 1 || softOrHard != 11)
{
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "\nPlaese enter the number 1 or 11"<<endl;
checkSoftOrHard(pH);
}


}

}


}

bool userWantsToDraw(char& Draw)
{
cout << endl << "\nwould you like to hit or stand?";
cin >> Draw;
cout << "\n";
if(Draw == 'h' || Draw == 'H')
{
return(true);

}

else
{
return(false);

}

}

void checkBust(const int pH[], const int dH[], char Play) 
{
int playerScore = getHandValue(pH);
int dealerscore = getHandValue(dH);
if(playerScore > 21) 
{
cout<<"You bust with " <<getHandValue(pH)<<" points."<<endl; 
cout << "\n" << endl; 
win--;
cout << "Winnings multiplier: " << win << endl; 
playAnotherHand(Play);
}
else if (dealerscore > 21)
{
scoreBoard(pH, dH); 
cout << "\n" << endl; 
cout << "The Dealer went bust. You An!" << endl;
cout << "\n" << endl; 
win++; 
cout << "Winnings multiplier: " << win << endl; 
playAnotherHand(Play);

}


}

void hitUntilStand(int dH[], int deck[], int pH[])
{
for(int i = 0; i < 9; i++)
{
if(getHandValue(dH) < 17)
{
if(level == 1)
{
addToHand(dH, getTopCard(deck));
}

else if( level == 2)
{
addToHand(dH, getTopCard(deck));
softOrHardAI(dH, pH);
}

}

else{
if(i == 0)
{
cout << "The Dealer stands"<< endl;
break;
}

else if (i == 1)
{
cout<< "the dealer hit a card and stands"<< endl;
break;

}
}
if(level == 1);
else if( level == 2)
{
softOrHardAI(dH, pH);

}

}


}

int getHandValue(const int hand[])
{
int addCardValues = 0;
for(int i = 0; i < 9; i++)
{

addCardValues = addCardValues + CardValue(hand[i]);

}
return addCardValues;

}

int CardValue(int card)
{
int cardVal;
switch(card % 100)
{
case 1:
cardVal = 11;
break;

case 11:
case 12:
case 13:
        cardVal = 10;
        break;

case 14:
        cardVal = 1;
        break;

default: 
        cardVal = (card % 100);
}

return cardVal;

}

void scoreBoard(const int pH[], const int dH[])
{
cout << "Player hand: "; 
showCards(pH, 10, false); 
cout << " ("<< getHandValue(pH) << "pts)."<<endl;
cout <<"v.s." << endl; 
cout <<"Dealer hand: "; 
showCards(dH, 10, false); 
cout << " ("<< getHandValue(dH) << "pts)."<<endl; 

}

void backdoorKenny(const int hand[])
{
 if((CardValue(hand[0])%100 == 10)&&(CardValue(hand[1])%100 == 11))
 {
cout << "\n\n"; 
cout <<"You pulled a Backdoor Kenny!\n" <<endl; 
cout << "Win an additional 1:4 payout\n" << endl; 
win = win + .25; 
cout << "Winnings multiplier: " << win << endl; 
}

}

void ShowCard(int card)
{
if (card == 0)
{

cout <<"";

}

else
{
switch(card % 100)
{
case 1:
cout <<"A";
break;

case 11:
cout <<"J";
break;
case 12:
cout <<"K";
break;
case 13:
cout <<"Q";
break;
case 14:
cout <<"A";
break;
default: 
cout << card % 100;
}

}

if(card == 0)
{
cout <<"";   
}

else 
{
if((card >= 101) && (card <=114))
{
cout << static_cast<char>(3);

}
else if((card >= 201) && (card <=214))
{
cout << static_cast<char>(4);
}

else if((card >= 301) && (card <=314))
{
cout << static_cast<char>(5);
}

else if((card >= 401) && (card <=414))
{
cout << static_cast<char>(6);
}

}

}

void dumpDeck(int deck[], int size)
{
for(int i = 0; i < size; i++)
{
cout << i + 1<< ".)" << deck[i] <<endl;

}

}

int getRandomNumber(int low, int high)
{
static bool firstTime=true; 
int randNum; 

if (firstTime)
{
srand( static_cast<unsigned int>(time(NULL)) );
firstTime=false;

}
randNum = rand() % (high-low+1) + low;
return randNum;

}

void softOrHardAl(int dH[], int pH[])
{
 for(int i=0; i<9; i++)
 {
      if(CardValue(dH[i]) == 1 || CardValue(dH[i]) == 11)
      {
             if(CardValue(dH[i]) == 11)
             {
                if (getHandValue(dH) - CardValue(dH[i]) + 1 > getHandValue(pH))
                {
                    if (getHandValue(dH) - CardValue(dH[i]) + 1 < 22)
                    {
                        dH[i] = dH[i] + 13;
                    }
                }
                else if (getHandValue(dH) > 21)
                {
                    dH[i] = dH[i] + 13;

                }
                

             }
            else
            {  
                if (getHandValue(dH) - CardValue(dH[i]) + 11 > getHandValue(pH)) 
                {
                    if (getHandValue(dH) - CardValue(dH[i]) + 11 < 22)
                    {
                        dH[i] = dH[i] - 13;
                    }

                }

            }

      }
     
 }


}

void whoWins(const int pH[], const int dH[])
{
int playerScore = getHandValue(pH); 
int dealerScore = getHandValue(dH);
scoreBoard(pH, dH); 
if((playerScore < 22) && (playerScore > dealerScore) || ((dealerScore > 21) && (playerScore < 22) ) )
{
 cout << "\n";
 cout << "You win!" << endl;
 win++;

}
else
{
 if(playerScore == dealerScore)
 {
    cout<<"\n"; cout<<"Push in the Dealer's favor. 0:1 payout." << endl; 

 }

 else
 {
    cout << "\n"; 
    cout << "You lose." << endl;
    win--; 

 }


}


}

bool playAnotherHand(char& Play)
{
cout << endl << "\nWould you like to play another hand? (Y/N) "; 
cin >> Play; 
cout << "\n" << endl;

if(Play == 'y' || Play == 'v') 
{
playOneHand();
//GO to main game to restart
return(true);
}
 else 
 { 
 //If don't, exit the program. 
 return(false);

}

}
