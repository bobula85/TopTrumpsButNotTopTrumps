#pragma once

#include <vector>
#include <memory>

#include "Card.h"

class Player
{
public:
	
	Player(int number);
	~Player();

	void AddPlayableCard(Card* card);					// Takes a card and adds it to the players playble cards using the car copy constructor
	void AddScorableCard(Card* card);					// Takes a card and adds it to the players scorabel cards using the car copy constructor

	void RemovePlayableCard(Card* card);				// Use find algorithm to remove a played card

	std::vector<Card*>& GetScorableCards() { return m_vScorabelCards; }		// Accessor function so that Game can tally player scores and decide winner
	std::vector<Card*>& GetPlayableCards() { return m_vPlayableCards; }		// Accessor function so that Game can tally player scores and decide winner

	Card* PlayCard();										// Returns card played by player

	int GetPlayerNumber() { return m_iPlayerNumber; }

private:

	int m_iPlayerNumber;

	std::vector<std::shared_ptr<Card>> m_vPlayableCardsSmart;		// smart pointer implementation for memory leak protection
	std::vector<std::shared_ptr<Card>> m_vScorabelCardsSmart;		// smart pointer implementation for memory leak protection

	std::vector<Card*> m_vPlayableCards;		// Vector to hold the players curretly playable cards
	std::vector<Card*> m_vScorabelCards;		// Vector to hold the cards that the player has won
};