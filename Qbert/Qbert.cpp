#include <MiniginPCH.h>
#include <Minigin.h>
#include "QbertGame.h"
#include "SceneManager.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

int main(int, char* [])
{
	dae::Minigin engine;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");
	qbert::QbertGame* qbertGame = new qbert::QbertGame(scene, qbert::QbertGame::GameMode::SINGLE_PLAYER);
	engine.Run(qbertGame);
	return 0;
}