
#include "Game.h"

#include <iostream>


int main(void)
{
	int maxCardValue, numSuits, numPlayers;

	std::cout << "Set maximum card value: ";
	std::cin >> maxCardValue;

	std::cout << "Set number of suits: ";
	std::cin >> numSuits;

	std::cout << "Set number of players: ";
	std::cin >> numPlayers;

	Game* currentGame = new Game(maxCardValue, numSuits, numPlayers);

	while (currentGame->GetGameState() != GameStates::EXIT)
	{
		switch (currentGame->GetGameState())
		{
			case GameStates::PLAYING:
			{
				currentGame->PlayRound();
				break;
			}
			case GameStates::SCORING:
			{
				currentGame->ScoreGame();
				break;
			}
		}
	}

	return 0;
}