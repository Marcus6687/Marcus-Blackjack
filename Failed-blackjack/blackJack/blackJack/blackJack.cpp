#include <iostream>
#include<string>
#include <Hand.h>
#include <Game.h>
#include <Deck.h>
#include <Player.h>
#include <genericPlayer.h>
#include <Card.h>

using namespace std;

//function prototypes
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

int main()
{
	cout << "\t\tWelcome to blackjack!\n\n";
	int numPlayer = 0;
	while (numPlayer < 1 || numPlayer > 7)
	{
		cout << "How many Player? (1-7): \n";
		cin >> numPlayers;
	}
	vector<string>names;
	string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Enter player name: \n";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	//the game loop
	Game aGame(names);
	char again = 'y'
		while (again != 'n' && again != 'N')
		{
			aGame.Play();
			cout << "\n Do you want to play again? (Y/N): \n";
			cin >> again;
		}
	return 0;
}