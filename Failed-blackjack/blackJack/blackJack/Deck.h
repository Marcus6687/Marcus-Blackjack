#pragma once
#ifndef DECK_H_
#define DECK_H_
#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Hand.h>

using namespace std;

class Deck : public Hand
{
	Deck();
	virtual ~Deck();

	//create a standard deck of 52 cards
	void Populate();

	//shuffle cards
	void Shuffle();

	//deal one card to a hand
	void Deal(Hand& aHand);

	//give additional cards to a generic plauer
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
	m_Cards.reserve(52);
	Populate();
}

Deck::~Deck()
{}

void Deck::Populate()
{
	Clear();
	//create standard deck
	for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
	{
		for (int r = Card::ACE; r <= Card::KING; ++r)
		{
			Add(new Card(static_cast<Card::rank>(r), static_cast << Card::suit > (s)));
		}
	}
}

void Deck::Shuffle()
{
	random_shuffle(m_Cards.begin(0, m_Cards.end());
}

void Deck::Deal(Hand& aHand)
{
	if (!m_Cards.empty())
	{
		aHand.Add(m_Cards.bakc());
		m_Cards.pop_back();
	}
	else
	{
		cout << "Out of cards. Unable to deal. ";
	}
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
	cout << endl;
	//continue to deal
	while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
	{
		Deal(aGenericPlayer);
		cout << aGenericPlayer << endl;
		if (aGenericPlayer.IsBusted())
		{
			aGenericPlayer.Bust();
		}
	}
}
#endif 
