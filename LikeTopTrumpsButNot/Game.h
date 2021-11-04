#pragma once

#include <vector>
#include <memory>

class Player;
class PlayerSmart;
class Card;

enum class GameStates
{
	NONE = 0,
	PLAYING,
	SCORING,
	EXIT
};

struct PlayerTurn
{
	Card*		card;
	Player*		player;

};

struct PlayerScore
{
	int totalScore;
	Player* player;

};


// Smart pointer implementations
struct PlayerTurnSmart
{
	std::shared_ptr<Card> card;
	std::shared_ptr<PlayerSmart> player;
};

struct PlayerScoreSmart
{
	int totalScore;
	std::shared_ptr<PlayerSmart> player;

};


class Game
{
public:

	Game(int highestCardValue, int numSuits, int numPlayers, bool smart = false);

	~Game();

	// Get game state for game loop
	GameStates GetGameState() { return m_eState; }

	// Calls play card for each player int he players vector
	void PlayRound();

	// This is called at the end of the game and tallys all player scores based on thier scorable cards 
	void ScoreGame();

	// Calls play card for each player int he players vector
	void PlayRoundSmart();

	// This is called at the end of the game and tallys all player scores based on thier scorable cards 
	void ScoreGameSmart();

private:

	// InitCards loops though the max value and numsuits values to init the cards
	void InitCards();

	// Create player objects based on the number of players
	void InitPlayers();

	// DealCards takes a ref to the vector of players and randomly deals all card to players
	void DealCards();

	// Get cards played by players
	void PlayCards();

	// Check which player played the highest card
	void CheckRoundWinner();

	// Remove played cards from player hand
	void RemovePlayedCards();

	void CheckGameEnd();

	std::vector<Card*>						m_vDeck;				// Vector to hold the deck of cards. If speed of access was of importance the multi set could be used instead
	std::vector<Player*>					m_vPlayers;				// Vector to hold players. vector used so that a variable amount of players can be set

	std::vector<PlayerTurn*>				roundCards;				// Vector to hold the card/player pointers for each round


//////////////////////////////////////////////	Smart pointer implementation	/////////////////////////////////////////


	// Smart pointer version of card initialisation
	void InitCardsSmart();

	// Create player objects based on the number of players
	void InitPlayersSmart();

	// DealCards takes a ref to the vector of players and randomly deals all card to players
	void DealCardsSmart();

	void PlayCardsSmart();

	void CheckRoundWinnerSmart();

	void RemovePlayedCardsSmart();

	void CheckGameEndSmart();


	int m_iMaxCardValue;			// Hold the maximum card value (std cards would be 13, ace to king)
	int m_iNumSuits;				// Holds the number of suits (std cards is 4, hearts, spades, clubs, dimonds)
	int m_iNumPlayers;				// Variable to hold the total number of players or the game (set at construction)

	GameStates m_eState;

	std::vector<std::shared_ptr<Card>>					m_vDeckSmart;			// Smart Pointer version of the deck vector (no deletes required!)
	std::vector<std::shared_ptr<PlayerSmart>>			m_vPlayersSmart;		// Smart Pointer version of the player vector (no deletes required!)
	std::vector<std::shared_ptr<PlayerTurnSmart>>		m_vRoundCardsSmart;		// Holds the cards played by players for the current hand
};