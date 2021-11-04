
#include "Game.h"

#include <iostream>

#define SMART

int main(void)
{
	int maxCardValue, numSuits, numPlayers;

	std::cout << "Set maximum card value: ";
	std::cin >> maxCardValue;

	std::cout << "Set number of suits: ";
	std::cin >> numSuits;

	std::cout << "Set number of players: ";
	std::cin >> numPlayers;

#ifdef SMART
	Game* currentGame = new Game(maxCardValue, numSuits, numPlayers, true);
#else
	Game* currentGame = new Game(maxCardValue, numSuits, numPlayers);
#endif

	while (currentGame->GetGameState() != GameStates::EXIT)
	{
		switch (currentGame->GetGameState())
		{
			case GameStates::PLAYING:
			{
#ifdef SMART
				currentGame->PlayRoundSmart();
#else
				currentGame->PlayRound();
#endif
				break;
			}
			case GameStates::SCORING:
			{
#ifdef SMART
				currentGame->ScoreGameSmart();
#else
				currentGame->ScoreGame();
#endif
				
				break;
			}
		}
	}

	return 0;
}