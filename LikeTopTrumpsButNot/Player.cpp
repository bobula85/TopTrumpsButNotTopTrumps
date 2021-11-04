#include "Player.h"

#include <iostream>

Player::Player(int number)
	: m_iPlayerNumber(number)
{

}

Player::Player(const Player& OtherPlayer)
	:m_iPlayerNumber (OtherPlayer.m_iPlayerNumber), 
	m_vPlayableCards(OtherPlayer.m_vPlayableCards), 
	m_vScorabelCards(OtherPlayer.m_vScorabelCards)
{
}

Player::Player(Player&& OtherPlayer) noexcept
	: m_iPlayerNumber(0),
	m_vPlayableCards({}),
	m_vScorabelCards({})
{
	Swap(*this, OtherPlayer);
}

Player::~Player()
{

}

Player& Player::operator=(const Player& otherPlayer)
{
	m_iPlayerNumber  = otherPlayer.m_iPlayerNumber;
	m_vPlayableCards = otherPlayer.m_vPlayableCards;
	m_vScorabelCards = otherPlayer.m_vScorabelCards;

	return *this;
}

Player& Player::operator=(Player&& OtherPlayer) noexcept
{
	if (&OtherPlayer != this)
		Swap(*this, OtherPlayer);

	return *this;
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


//////////////////////////////////////////////////	Player using smart pointers	/////////////////////////////////////////////////



PlayerSmart::PlayerSmart(int number)
	: m_iPlayerNumber(number)
{

}

void PlayerSmart::AddPlayableCardSmart(std::shared_ptr<Card> card)
{
	m_vPlayableCardsSmart.push_back(card);
}

void PlayerSmart::AddScorableCardSmart(std::shared_ptr<Card> card)
{
	m_vScorabelCardsSmart.push_back(card);
}

void PlayerSmart::RemovePlayableCardSmart(std::shared_ptr<Card> card)
{
	auto findResult = std::find_if(m_vPlayableCardsSmart.begin(), m_vPlayableCardsSmart.end(), [&](std::shared_ptr<Card> currentCard)
									{ return card->GetValue() == currentCard->GetValue(); });

	if (findResult != std::end(m_vPlayableCardsSmart))
		m_vPlayableCardsSmart.erase(findResult);
}

std::shared_ptr<Card> PlayerSmart::PlayCardSmart()
{
	std::cout << "Player " << m_iPlayerNumber << " please play a card" << std::endl;

	for (std::shared_ptr<Card> card : m_vPlayableCardsSmart)
		std::cout << card->GetValue() << " ";
	std::cout << std::endl;

	int x;

	std::cout << "Type a number: ";
	std::cin >> x;

	auto findResult = std::find_if(m_vPlayableCardsSmart.begin(), m_vPlayableCardsSmart.end(), 
									[&](std::shared_ptr<Card> card) { return card->GetValue() == x; });

	if (findResult == std::end(m_vPlayableCardsSmart))
		std::cout << "Please enter valid card! " << std::endl;
	else
		return *findResult;

	return nullptr;
}
