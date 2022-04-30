#pragma once
#ifndef HAND_H_
#define HAND_H_
#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Hand
{
public:
	Hand();
	virtual ~Hand();
	//adds a card to the hand
	inline void Hand::Add(Card* pCard);

	//clears hand of all cards
	void Clear();

	//gets hand total value, treat ace as 1 or 11
	int GetTotal() const;
protected:
	vector<Card*> m_Cards;
};
Hand::Hand()
{
	m_Cards.reserve(7);
}
Hand::~Hand()
{
	Clear();
}
inline void Hand::Add(Card* pCard)
{
}
void Hand::Clear()
{
	vector<Card*>::iteraotr iter = m_Cards.begin();
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		delete* iter;
		*iter = 0;
	}
	//clear vector of pointers
	m_Cards.clear();
}
int Hand::GetTotal() const
{
	//if no card in hand, return 0
	if (m_Cards.empty())
	{
		return 0;
	}

	//if a first card has 0 vlaue
	if (m_Cards[0]->GetValue() == 0)
	{
		return 0;
	}

	//addup card value
	int total = 0;
	vector<Card*>::const_iterrator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->GetValue();
	}

	//determine if hadn contains an ace
	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->GetValue() == Card::Ace)
		{
			containsAce = true;
		}
	}

	//if hand contains ac and total is low enough, treat ace as 11
	if (containsAce && total <= 11)
	{
		//add only 10
		total += 10;
	}
	return total;
}
#endif 