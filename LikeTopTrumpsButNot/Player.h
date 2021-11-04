#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Card.h"

class Player
{
public:
	
	Player(int number);

	Player(const Player& OtherPlayer);

	Player(Player&& OtherPlayer) noexcept;

	~Player();

	Player& operator=(const Player& otherPlayer);
	Player& operator=(Player&& that) noexcept;

	friend void Swap(Player& lhs, Player& rhs) noexcept
	{
		std::swap(lhs.m_iPlayerNumber, rhs.m_iPlayerNumber);
		std::swap(lhs.m_vPlayableCards, rhs.m_vPlayableCards);
		std::swap(lhs.m_vPlayableCards, rhs.m_vPlayableCards);
	}





	void AddPlayableCard(Card* card);					// Takes a card and adds it to the players playble cards using the car copy constructor
	void AddScorableCard(Card* card);					// Takes a card and adds it to the players scorabel cards using the car copy constructor

	void RemovePlayableCard(Card* card);				// Use find algorithm to remove a played card

	std::vector<Card*>& GetScorableCards() { return m_vScorabelCards; }		// Accessor function so that Game can tally player scores and decide winner
	std::vector<Card*>& GetPlayableCards() { return m_vPlayableCards; }		// Accessor function so that Game can tally player scores and decide winner

	Card* PlayCard();										// Returns card played by player

	int GetPlayerNumber() { return m_iPlayerNumber; }

private:

	int m_iPlayerNumber;

	std::vector<Card*> m_vPlayableCards;		// Vector to hold the players curretly playable cards
	std::vector<Card*> m_vScorabelCards;		// Vector to hold the cards that the player has won
};


class PlayerSmart
{
public:

	// Use of smart pointers negates the necessety for rule of 3/5 so rule of 0 applies

	PlayerSmart(int number);

	PlayerSmart(const PlayerSmart& OtherPlayer) = default;
	PlayerSmart& operator=(const PlayerSmart& otherPlayer) = default;

	~PlayerSmart() = default;

	void AddPlayableCardSmart(std::shared_ptr<Card> card);					// Takes a card and adds it to the players playble cards using the car copy constructor
	void AddScorableCardSmart(std::shared_ptr<Card> card);					// Takes a card and adds it to the players scorabel cards using the car copy constructor

	void RemovePlayableCardSmart(std::shared_ptr<Card> card);				// Use find algorithm to remove a played card

	std::vector<std::shared_ptr<Card>>& GetScorableCardsSmart() { return m_vScorabelCardsSmart; }		// Accessor function so that Game can tally player scores and decide winner
	std::vector<std::shared_ptr<Card>>& GetPlayableCardsSmart() { return m_vPlayableCardsSmart; }		// Accessor function so that Game can tally player scores and decide winner

	std::shared_ptr<Card> PlayCardSmart();										// Returns card played by player

	int GetPlayerNumberSmart() { return m_iPlayerNumber; }

private:

	int m_iPlayerNumber;

	std::vector<std::shared_ptr<Card>> m_vPlayableCardsSmart;		// smart pointer implementation for memory leak protection
	std::vector<std::shared_ptr<Card>> m_vScorabelCardsSmart;		// smart pointer implementation for memory leak protection
};