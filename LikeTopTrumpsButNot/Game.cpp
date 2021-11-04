#include "Player.h"
#include "Card.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <algorithm>

Game::Game(int highestCardValue, int numSuits, int numPlayers, bool smart)
	: m_iMaxCardValue(highestCardValue), m_iNumSuits(numSuits), m_iNumPlayers(numPlayers)
{
	if (smart)
	{
		InitCardsSmart();

		InitPlayersSmart();

		DealCardsSmart();
	}
	else
	{
		InitCards();

		InitPlayers();

		DealCards();
	}

	m_eState = GameStates::PLAYING;
}

Game::~Game()
{
	m_vDeck.clear();
	m_vPlayers.clear();
	roundCards.clear();
}

// Initialise the cards usinf the games init values for max card values and number of suits
void Game::InitCards()
{
	for (int i = 0; i < m_iNumSuits; i++)
	{
		for (int j = 0; j < m_iMaxCardValue; j++)
			m_vDeck.push_back(new Card(j, i));
	}
}

// Init player objects using game init value for num players
void Game::InitPlayers()
{
	for (int i = 0; i < m_iNumPlayers; i++)
		m_vPlayers.push_back(new Player(i));
}

void Game::DealCards()
{
	// Use randome shuffle algorithm
	std::random_shuffle(m_vDeck.begin(), m_vDeck.end());

	int playerNumber = 0;

	// Loop through each card and give it to a player
	for (auto card : m_vDeck)
	{
		m_vPlayers[playerNumber]->AddPlayableCard(card);

		// increment player to be given a card
		playerNumber++;

		// reset player number if all players have a card
		if (playerNumber >= m_iNumPlayers)
			playerNumber = 0;
	}
}

void Game::PlayRound()
{
	roundCards.clear();

	PlayCards();

	CheckRoundWinner();

	RemovePlayedCards();

	CheckGameEnd();

	roundCards.clear();
}

void Game::PlayCards()
{
	// Get vector of played cards by player
	for (auto player : m_vPlayers)
	{
		PlayerTurn* temp = new PlayerTurn();
		temp->card = player->PlayCard();
		temp->player = player;

		roundCards.push_back(temp);
	}
}

void Game::CheckRoundWinner()
{
	PlayerTurn* highestCard = roundCards[0];

	// check to see who played the highest card
	for (PlayerTurn* turn : roundCards)
	{
		if (turn->card->GetValue() > highestCard->card->GetValue())
			highestCard = turn;
	}

	// Use the player linked to the turn struct to add a scorable card to thier scorable cards vector 
	highestCard->player->AddScorableCard(highestCard->card);
}

void Game::RemovePlayedCards()
{
	// Remove the cards used from the playes playable cards vector
	for (PlayerTurn* turn : roundCards)
	{
		turn->player->RemovePlayableCard(turn->card);
	}
}

void Game::CheckGameEnd()
{
	// Check if all of the playable cards have been used and if so then set the game state to scoring
	if (m_vPlayers[0]->GetPlayableCards().size() == 0)
		m_eState = GameStates::SCORING;
}


void Game::ScoreGame()
{
	// Vector to hold player scores
	std::vector<PlayerScore*> playerScoreTotals;

	// Calculate total score for each player
	for (auto player : m_vPlayers)
	{
		PlayerScore* tempScore = new PlayerScore();
		tempScore->player = player;

		for (Card* card : player->GetScorableCards())
			tempScore->totalScore += card->GetValue();

		playerScoreTotals.push_back(tempScore);
	}

	Player* winner = m_vPlayers[0];
	int highestScore = 0;

	// Check for highest score
	for (auto score : playerScoreTotals)
	{
		if (score->totalScore > highestScore)
		{
			highestScore = score->totalScore;
			winner = score->player;
		}
	}

	// Declare the winner
	std::cout << " The winner is....DRUM ROLLLL.... Pllllaaayyeeerrrrr.... " << winner->GetPlayerNumber() << std::endl;
	std::cout << " With a total score of " << highestScore << std::endl;

	std::cin.get();

	m_eState = GameStates::EXIT;
}


// Smart pointer implementations of the init cards/players functions negate the need for manual deletions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void Game::InitCardsSmart()
{
	for (int i = 0; i < m_iNumSuits; i++)
	{
		for (int j = 0; j < m_iMaxCardValue; j++)
			m_vDeckSmart.push_back(std::make_shared<Card>(j, i));
	}
}

void Game::InitPlayersSmart()
{
	for (int i = 0; i < m_iNumPlayers; i++)
		m_vPlayersSmart.push_back(std::make_shared<PlayerSmart>(i));
}


void Game::DealCardsSmart()
{
	// Use randome shuffle algorithm
	std::random_shuffle(m_vDeckSmart.begin(), m_vDeckSmart.end());

	int playerNumber = 0;

	// Loop through each card and give it to a player
	for (auto card : m_vDeckSmart)
	{
		m_vPlayersSmart[playerNumber]->AddPlayableCardSmart(card);

		// increment player to be given a card
		playerNumber++;

		// reset player number if all players have a card
		if (playerNumber >= m_iNumPlayers)
			playerNumber = 0;
	}
}

void Game::PlayRoundSmart()
{
	m_vRoundCardsSmart.clear();

	PlayCardsSmart();

	CheckRoundWinnerSmart();

	RemovePlayedCardsSmart();

	CheckGameEndSmart();

	m_vRoundCardsSmart.clear();
}

void Game::PlayCardsSmart()
{
	// Get vector of played cards by player
	for (auto player : m_vPlayersSmart)
	{
		auto temp = std::make_shared<PlayerTurnSmart>();
		temp->card = player->PlayCardSmart();
		temp->player = player;

		m_vRoundCardsSmart.push_back(temp);
	}
}

void Game::CheckRoundWinnerSmart()
{
	auto highestCard = m_vRoundCardsSmart[0];

	// check to see who played the highest card
	for (auto turn : m_vRoundCardsSmart)
	{
		if (turn->card->GetValue() > highestCard->card->GetValue())
			highestCard = turn;
	}

	// Use the player linked to the turn struct to add a scorable card to thier scorable cards vector 
	highestCard->player->AddScorableCardSmart(highestCard->card);
}

void Game::RemovePlayedCardsSmart()
{
	// Remove the cards used from the playes playable cards vector
	for (auto turn : m_vRoundCardsSmart)
	{
		turn->player->RemovePlayableCardSmart(turn->card);
	}
}

void Game::CheckGameEndSmart()
{
	// Check if all of the playable cards have been used and if so then set the game state to scoring
	if (m_vPlayersSmart[0]->GetPlayableCardsSmart().size() == 0)
		m_eState = GameStates::SCORING;
}


void Game::ScoreGameSmart()
{
	// Vector to hold player scores
	std::vector<std::shared_ptr<PlayerScoreSmart>> playerScoreTotals;

	// Calculate total score for each player
	for (auto player : m_vPlayersSmart)
	{
		auto tempScore = std::make_shared<PlayerScoreSmart>();
		tempScore->player = player;

		for (auto card : player->GetScorableCardsSmart())
			tempScore->totalScore += card->GetValue();

		playerScoreTotals.push_back(tempScore);
	}

	auto winner = m_vPlayersSmart[0];
	int highestScore = 0;

	// Check for highest score
	for (auto score : playerScoreTotals)
	{
		if (score->totalScore > highestScore)
		{
			highestScore = score->totalScore;
			winner = score->player;
		}
	}

	// Declare the winner
	std::cout << " The winner is....DRUM ROLLLL.... Pllllaaayyeeerrrrr.... " << winner->GetPlayerNumberSmart() << std::endl;
	std::cout << " With a total score of " << highestScore << std::endl;

	std::cin.get();

	m_eState = GameStates::EXIT;
}

/// ///////////////////////////////////////////////////////////////////////////////////////////