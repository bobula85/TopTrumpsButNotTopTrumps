#include "Player.h"

#include <iostream>

Player::Player(int number)
	: m_iPlayerNumber(number)
{
}

Player::~Player()
{
}

void Player::AddPlayableCard(Card* card)
{
	m_vPlayableCards.push_back(card);
}

void Player::AddScorableCard(Card* card)
{
	m_vScorabelCards.push_back(card);
}

void Player::RemovePlayableCard(Card* card)
{
	auto findResult = std::find_if(m_vPlayableCards.begin(), m_vPlayableCards.end(), [&](Card* currentCard) { return card->GetValue() == currentCard->GetValue(); });

	if (findResult != std::end(m_vPlayableCards))
		m_vPlayableCards.erase(findResult);
}

Card* Player::PlayCard()
{
	std::cout << "Player " << m_iPlayerNumber << " please play a card" << std::endl;

	for (Card* card : m_vPlayableCards)
		std::cout << card->GetValue() << " ";
	std::cout << std::endl;

	int x;

	std::cout << "Type a number: ";
	std::cin >> x;

	auto findResult = std::find_if(m_vPlayableCards.begin(), m_vPlayableCards.end(), [&](Card* card) { return card->GetValue() == x; });

	if (findResult == std::end(m_vPlayableCards))
		std::cout << "Please enter valid card! " << std::endl;
	else
		return *findResult;

	return nullptr;
}


