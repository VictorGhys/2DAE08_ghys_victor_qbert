#include <MiniginPCH.h>
#include <Minigin.h>
#include "QbertGame.h"

int main(int, char* [])
{
	dae::Minigin engine;
	qbert::QbertGame* qbertGame = new qbert::QbertGame();
	engine.Run(qbertGame);
	delete qbertGame;
	return 0;
}