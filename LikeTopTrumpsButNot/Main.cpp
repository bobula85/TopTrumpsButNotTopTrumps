
#include "Game.h"


int main(void)
{

	Game* currentGame = new Game(4, 1, 2);

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