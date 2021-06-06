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
	// to find memory leak
	/*HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);*/
	//_CrtSetBreakAlloc(417);

	dae::Minigin engine;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");
	qbert::QbertGame* qbertGame = new qbert::QbertGame(scene, qbert::QbertGame::GameMode::SINGLE_PLAYER);
	engine.Run(qbertGame);

	//_CrtDumpMemoryLeaks();
	return 0;
}