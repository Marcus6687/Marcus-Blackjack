#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <genericPlayer.h>

using namespace std;

class Player : public GenericPlayer
{
public:
	Player(const string& name = "");
	virtual ~Player();

	//return whter or not the player wants another hit
	virtual bool IsHitting() const;

	//announces that the plaer wins
	void Win() const;

	//announces that the player loses
	void Lose() const;

	//announces that the player pushes
	void Push() const;
};

Player::Player(const string& name) :
	GenericPlayer(name)
{}
bool Player::IsHitting() const
{
	cout << m_Name << ", do you want a hit? (Y/N): ";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}

void Player::Lose() const
{
	cout << m_Name << " loses. \n";
}

void Player::Push() const
{
	cout << m_Name << " pushes. \n";
}
#endif 