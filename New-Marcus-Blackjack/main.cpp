#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
 
//Declare namespace
using namespace std;
 
//Prototype functions.
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
void whoWins(const int pHand[], const int dHand[]);
void checkBust(const int pHand[], const int dHand[], char Play);
void blackJack(const int pHand[], const int dHand[], char Play);
void naturalBlackJack(const int pHand[], const int dHand[], char Play);
void playOneHand();
void scoreBoard(const int pHand[], const int dHand[]);
void backdoorKenny(const int hand[]);
void checkSoftOrHard(int pHand[]);
void softOrHardAI(int dHand[], int pHand[]);
void chooseLevelOfDificulty();
void showRules();
void addToHand(int hand[], int cardToAdd);
void hitUntilStand(int dHand[], int deck[], int pHand[]);
 
//Declare global Variables
int topCard = 0;
float win = 1.00;
int level;
 
int main()
{
	showRules();
	chooseLevelOfDificulty();
	playOneHand();
	return 1;
}
 
/* ==================================================
Name: showRules
Desc: Displays the game rules
Parameters:
   None.
Return:
   void.
================================================== */
void showRules()
{
cout<<"Welcome to Blackjack"<<endl;
cout<<"Here are the rules"<<endl;
cout<<"1 Aces can be either one or 11 points"<<endl;
cout<<"2 dealer wins ties unless player has a blackjack"<<endl;
cout<<"Winning conditions are:"<<endl;
cout<<"Your score beats dealers score"<<endl;
cout<<"If your score is higher than dealers"<<endl;

}
 
void chooseLevelOfDificulty()
{
	//Prompt user and store input
	cout << "\n";
	cout << "Level of Difficulty: Beginner (1), Expert (2). ";
	cin >> level;
	cout << "\n";
 
	//If input is not a 1..
	if(level != 1)
	{
		//...or a 2.
		if(level != 2)
		{
			//Clears input error flags and removes everything currently in the input buffer. 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
 
			//Display error message and restart function. 
			cout << "Please enter your level of difficulty using the number 1 or 2." << endl;
			chooseLevelOfDificulty();
		}
	}			
}
 

void playOneHand()
{
	//Declare local variable
	char Play = 'N';
 
	//Start the game at least once and repeat while Player wants to. 
	do
	{					
		//Declare local variable
		char Draw = 'H';
 
		//Declare, initialize and shuffle the deck.
		int deck[52];
		initializeDeck(deck);
		shuffle(deck, 51);
 
		//Declare and initialize Player and Dealer hands.
		int pHand[10] = {0};
		int dHand[10] = {0};
	
		//Deal first round
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));
 
		//Display an explanation  of what is happening
		cout << "//////////////////////////////////////////////////////////" << endl;
		cout << "\n" << endl;
		cout << "The Dealer shuffled and dealt you each your cards. ";
		cout << "\n" << endl;
 
		//Check for an automatic win.
		naturalBlackJack(pHand, dHand, 'y');
		blackJack(pHand, dHand, 'Y');
 
		//Display Player and Dealer hands
		cout << "Your hand:" << endl;
		showCards(pHand, 10, false);
		cout << "\n\nDealer's hand:" << endl;
		showCards(dHand, 10, true);
 
		//If Player has an Ace, see if Player want's to have a soft or hard hand.
		checkSoftOrHard(pHand);
		
		//Check if user wants to hit
		while (userWantsToDraw(Draw))
		{
			//Deal Player a card 
			//and display an explanation  of what is happening 
			addToHand(pHand, getTopCard(deck));
			cout << "The Dealer dealt you another card.\n" << endl;
			
			//Display Player's updated hand
			cout << "Your hand:" << endl;
			showCards(pHand, 10, false);
 
			//If Player has an Ace, see if Player want's to have a soft or hard hand.
			checkSoftOrHard(pHand);
 
			//Check to see if anyone lost
			checkBust(pHand, dHand, 'y');
 
			//Check to see if anyone won
			blackJack(pHand, dHand, 'Y');
		}
		
		//Dealer hits until at a soft 17
		hitUntilStand(dHand, deck, pHand);
		cout << endl;
 
		//Check to see if anyone lost
		checkBust(pHand, dHand, 'Y');
	
		//Check to see if anyone won
		blackJack(pHand, dHand, 'Y');
 
		//Compare scores and determine winner
		whoWins(pHand, dHand);
		cout << endl;
 
		//Display updated winnings multiplier
		cout << "Winnings multiplier: " << win << endl;
	}
	while (playAnotherHand(Play));
}
 

void initializeDeck(int deck[])
{
	//Declare local variables.
	int Rank = 101;
	int i = 0;
 
	//Hearts
	for (i = 0 ; i<=13; i++)
	{
		deck[i] = Rank++;
	}
 
	//Diamonds
	for (i = 13 ; i<=26; i++)
	{
		deck[i] = Rank++ + 100 - 14;
	}
 
	//Clubs
	for (i = 26 ; i<=39; i++)
	{
		deck[i] = Rank++ + 200 - 28;
	}
 
	//Spades
	for (i = 39 ; i<=51; i++)
	{
		deck[i] = Rank++ + 300 - 42;
	}
}
 

void shuffle(int deck[], int size)
{
	//Loop through deck an absurd amount of loops.
	for(int i = 0; i < 500; i++)
	{
		//Define local variables
		int T1 = 0;
		int R1 = getRandomNumber(0, size);
		int R2 = getRandomNumber(0, size);
 
		//Clone first card for safe keeping 
		//Replace first card with a new card
		//Replace the new card with the old card clone
		T1	= deck[R1];
		deck[R1] = deck[R2];
		deck[R2] = T1;
	}	
}
 

void ShowCard(int card)
{
	//Show nothing for non cards (ie.0)
	if(card == 0)
	{
		cout << "";
	}
	//Define Ranks.
	else
	{
		switch(card % 100)
		{
			case 1: 
				cout << "A";
				break;
			case 11: 
				cout << "J";
				break;
			case 12: 
				cout << "K";
				break;
			case 13: 
				cout << "Q";
				break;
			case 14://14 is a value created in checkSoftOrHard
				cout << "A";
				break;
 
			//For non-face cards, just use their 10s value as rank.
			default:
				cout << card % 100;
		} 
	}
 
	//Show nothing for non cards (ie.0)
	if(card == 0)
	{
		cout << "";
	}
	//Define Suits.
	else
	{
		//Hearts
	   if((card >= 101) && (card <=114))
		{
			cout << static_cast<char>(3);
		}
 
	   //Diamonds
		else if ((card >= 201) && (card <= 214))
		{
			cout << static_cast<char>(4);
		}
 
		//Clubs
		else if ((card >= 301) && (card <= 314))
		{
			cout << static_cast<char>(5);
		}
 
		//Spades
		else if ((card >= 401) && (card <= 414))
		{
			cout << static_cast<char>(6);
		}
	}
}
 

void showCards(const int deck[], int numCards, bool hideFirstCard)
{
	//Hide dealer's first card if true.
	if(hideFirstCard)
	{
		cout << "** ";
	}
 
	//Show dealer's first card if false.
	else
	{
		ShowCard(deck[0]);
		cout << " ";
	}
 
	//Display all the cards in the deck or hand
	//by showing their rank and suit graphic. 
	for(int i = 1; i < numCards; i++) 
	{
		//Show cards
		if(deck[i] != 0)
		{
			ShowCard(deck[i]);
			cout << " ";
		}
		
		//Show nothing for non cards (ie. 0). 
		else
		{
			cout << "";
		}
	}
}
 

void dumpDeck(int deck[], int size)
{
	//loop through the deck array and print each value.
	for(int i = 0; i < size; i++)
	{
		cout << i + 1 << ".) " << deck[i] << endl;
	}
}
 

int getRandomNumber(int low, int high) {
	static bool firstTime=true;
	int randNum;
 
	//if first time called, seed random number generator
	if (firstTime) {
		srand( static_cast<unsigned int>(time(NULL)) );
		firstTime=false;
	}
 
	//generate random number between given low and high values (inclusive)
	randNum = rand() % (high-low+1) + low;
 
	return randNum;
}
 

int CardValue(int card)
{
	//Declare local variable
	int cardVal;
 
	//Get the card's background 10s value and assign the card a point value
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
		//For non-face cards, just use their backround 10s value as point value.
		default:
		cardVal = (card % 100);
	}
	return cardVal;
}
 

int getTopCard(int deck[])
{
	//Loop through the deck
	for(int i = 0; i < 51; i++)
	{
		//Find a card that isn't empty
		if(deck[i] != 0)
		{
			//Clone card for safe keeping 
			//Replace first card with the empty card value
			//Return the clone of the card
			topCard = deck[i];
			deck[i] = 0;
			return topCard;
		}
	}
}
 

void addToHand(int hand[], int cardToAdd)
{
	//Loop through the hand
	for(int i = 0; i < 9; i++)
	{
		//If there is an empty card spot
		if(hand[i] == 0)
		{
			//Replace it with the card to add
			hand[i] = cardToAdd;
			break;//Only do this once by breaking the loop
		}
	}
}
 

void hitUntilStand(int dHand[], int deck[], int pHand[])
{
	//Loop through Dealer's hand
	for(int i = 0; i < 9; i++)
	{
		/*
		//If Player is an Expert
		if( level == 2)
		{
			//Loop through Dealer's hand
			for( int i = 0; i < 9; i++)
			{
				//Find a default Ace (11pts)
				if(CardValue(dHand[i]) == 11)
				{
					//Change Aces from default 11(soft) to 1(hard)
					dHand[i] = dHand[i] + 13; // A hard Ace (worth 1 point) has a background value ending in 14
				}
			}
		}
 
		//do nothing and clear this if of an else for the next if. 
		else;
		*/
 
		//If Dealer must hit
		if(getHandValue(dHand) < 17)
		{
			//If Player chose Beginner level dealer stands at soft 17
			if(level == 1)
			{
					//...add a card to the hand
					addToHand(dHand, getTopCard(deck));
			}
 
			//If Player chose Expert level dealer stands at Hard 17
			else if( level == 2)
			{
				//...add a card to the hand
				addToHand(dHand, getTopCard(deck));
 
				//Ensure Aces are handled intelligently to beat Player
				softOrHardAI(dHand, pHand);
			}
		}
		//Display how many cards Dealer hit if Dealer has 17 or more points...
		else
		{
			//Dealer didn't hit to get to 17
			if(i == 0)
			{
				cout << "The Dealer stands." << endl;
				break;
			}
			//Dealer hit once to get to 17
			else if(i == 1) 
			{
				cout << "The Dealer hit a card and stands." << endl;
				break;
			}
			//Dealer hit more than once to get to 17
			else
			{
				cout << "The Dealer hit " << i << " cards and stands." << endl;
				break;
			}	
		}
 
		//Run dealer AI again if player chose to play Expert
		//This is called again for the sake of redundancy.
		if(level == 1);
		else if( level == 2)
		{
			softOrHardAI(dHand, pHand);
		}
	}
}
 

int getHandValue(const int hand[])
{
	//Declare local variables
	int addCardValues = 0;
	
	//Loop through the hand and add up the card values
	for(int i = 0; i < 9; i++)
	{
		addCardValues = addCardValues + CardValue(hand[i]);
	}
 
	//Give the sum of the card values as the hand value
	return addCardValues;
}
 

bool playAnotherHand(char& Play)
{
	//Prompt user to see if they would like to play another hand.
	cout << endl << "\nWould you like to play another hand? (Y/N) ";
	cin >> Play;
	cout << "\n" << endl;
 
	//Go back to the main game logic function to restart if they do. 
	if(Play == 'y' || Play == 'Y') 
	{
		playOneHand();
		return(true);
	}
	//If they don't, exit the program.
	else
	{
		return(false);
	}
}
 

bool userWantsToDraw(char& Draw)
{
	//Prompt user to see if they would like to enter a new time.
	cout << endl << "\nWould you like to hit or stand? (H/S) ";
	cin >> Draw;
	cout << "\n";
	
	//If they do, return true and start the loop to draw another card.
	if(Draw == 'h' || Draw == 'H') 
	{
			return(true);
	}
	//If they don't, skip the loop. 
	else
	{
		return(false);
	}
}
 

void whoWins(const int pHand[], const int dHand[])
{
	//Declare local variables
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
 
	//Display the scoreboard
	scoreBoard(pHand,  dHand);
		
	//win tree
	//If Player scores less than 22
	if( (playerScore < 22) 
		//If Player's score is better than Dealer's score
		&& (playerScore > dealerScore) 
		//If Player's score is under 22 but Dealer's score is over 21
		|| ( (dealerScore > 21) 
			&& (playerScore < 22) ) )
	{
		//Display message and compute new winnings multiplier
		cout << "\n";
		cout << "You win!" << endl;
		win++;
	}
	//loos tree
	//If you don't win, you lose or tie. 
	else
	{
		//Tie
		//Display message
		if(playerScore == dealerScore)
		{
			cout << "\n";
			cout << "Push in the Dealer's favor. 0:1 payout." << endl;
		}
 
		//loose
		//Display message and compute new winnings multiplier
		else
		{
			cout << "\n";
			cout << "You lose." << endl;
			win--;
		}
	}
}
 

void checkBust(const int pHand[], const int dHand[], char Play)
{
	//Define local variables.
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
 
	//Check if Player busts. 
	//Display message, compute new winnings multiplier, ask to play another hand.
	if(playerScore > 21)
	{
		cout << "You bust with " << getHandValue(pHand) << " points." << endl;
		cout << "\n" << endl;
		win--;
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
 
	
	else if(dealerScore > 21)
	{
		scoreBoard(pHand,  dHand);
		cout << "\n" << endl;
		cout << "The Dealer went bust. You Win!" << endl;
		cout << "\n" << endl;
		win++;
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
}
 

void backdoorKenny(const int hand[])
{
	//If index 0 is a 10 and index 1 is an ace
	if((CardValue(hand[0])%100 == 10)&&(CardValue(hand[1])%100 == 11))
	{
		//Display message and compute new winnings multiplier.
		cout << "\n\n";
		cout << "You pulled a Backdoor Kenny!\n" << endl;
		cout << "Win an additional 1:4 payout\n" << endl;
		win = win + .25;
		cout << "Winnings multiplier: " << win << endl;
	}
}
 

void blackJack(const int pHand[], const int dHand[], char Play)
{
	//Define local Variables
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
 
	//If Player has blackjack but Dealer doesn't. 
	if((playerScore == 21) && (dealerScore != 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.
		cout << "\n\n";
		scoreBoard(pHand,  dHand); 
		cout << "\n";
		cout << "Blackjack! You win a 3:2 payout." << endl;
		win = win + 1.5;
		cout << "\n";
		cout << "Winnings multiplier: " << win << endl;
		backdoorKenny(pHand);
		playAnotherHand(Play);
	}
	//If both Player and Dealer have blackjack. 
	else if((playerScore == 21) && (dealerScore == 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.
		scoreBoard(pHand,  dHand);
		cout << "\n";
		cout << "The Dealer and you both got Blackjack. Push in your favor at 1:1 payout!" << endl;
		win++;
		cout << "\n";
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
}
 

void naturalBlackJack(const int pHand[], const int dHand[], char Play)
{
	//Define local variables
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
 
	//If Player has blackjack and Dealer doesnt
	if((playerScore == 21) && (dealerScore != 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.
		scoreBoard(pHand,  dHand); 
		cout << "\n";
		cout << "Natural Blackjack! You win a 3:2 payout.";
		win = win + 1.5;
		backdoorKenny(pHand);
		playAnotherHand(Play);
	}
}
 

void scoreBoard(const int pHand[], const int dHand[])
{
	//Display Player's cards/hand value
 	cout << "Player hand: ";
	showCards(pHand, 10, false);
	cout << " ("<< getHandValue(pHand) << "pts)."<<endl;
 
	cout <<"V.S." << endl;
 
	//Display Dealer's cards/hand value
	cout << "Dealer hand: ";
	showCards(dHand, 10, false);
	cout << " ("<< getHandValue(dHand) << "pts)."<<endl;
}
 
/* ==================================================
Name: checkSoftOrHard
Desc: Asks Player if they would like their Ace to
	  count as 1 or 11 points and then computes those
	  changes. 
Parameters:
   pHand[] (int) - Player's hand.
   dHand[] (int) - Dealer's hand.
Return:
   void
================================================== */
void checkSoftOrHard(int pHand[])
{
	//check cards in hand
	for(int i=0; i<9; i++)
	{
		//Define local variables.
		int checkAce = CardValue(pHand[i]);
		int softOrHard;
 
		//If card in hand is an Ace prompt Player for input
		if(checkAce == 1 || checkAce == 11)
		{
			cout << "\n";
			cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11): ";
			cin >> softOrHard;
 
			//If Player chooses 1
			if(softOrHard == 1)
			{
				if(checkAce == 11)
				pHand[i] = pHand[i] + 13;
			}
			
			//If Player chooses 11
			else if(softOrHard == 11)
			{
				if(checkAce == 1)
				{
					pHand[i] = pHand[i] - 13;
				}
			}
 
			//If player doesn't input 1 or 11
			else if (softOrHard != 1 || softOrHard != 11)
			{
				//Clears input error flags and removes everything currently in the input buffer. 
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				//Display error message and restart the function
				cout << "\nPlease enter the number 1 or 11." << endl;
				checkSoftOrHard(pHand);
			}
		}
	}
}
 
void softOrHardAI(int dHand[], int pHand[])
{
	//check cards in hand
	for(int i=0; i<9; i++)
	{
		//Find an Ace
		if(CardValue(dHand[i]) == 1 || CardValue(dHand[i]) == 11)
		{
			//If the Ace is worth 11 points...
			if(CardValue(dHand[i]) == 11)
			{
				//...change it to 1 point if that will beat player...
				if (getHandValue(dHand) - CardValue(dHand[i]) + 1 > getHandValue(pHand))
				{
					//...and not bust.
					if (getHandValue(dHand) - CardValue(dHand[i]) + 1 < 22)
					{
						dHand[i] = dHand[i] + 13;
					}
				}
 
				//Else if hand is a bust at 11, make it 1
				else if (getHandValue(dHand) > 21)
				{
					dHand[i] = dHand[i] + 13;
				}
			}
 
			//Else Ace is worth 1 point.
			else 
			{
				//Change it to 11 points if that will beat player...
				if (getHandValue(dHand) - CardValue(dHand[i]) + 11 > getHandValue(pHand))
				{
					//...and not bust.
					if (getHandValue(dHand) - CardValue(dHand[i]) + 11 < 22)
					{
						dHand[i] = dHand[i] - 13;
					}
				}
			}
		}
	}
}
 
 