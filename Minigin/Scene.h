#pragma once
#include "SceneManager.h"

namespace dae
{
	class Game;
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);
		void Remove(GameObject* object);
		void Destroy(GameObject* object);

		void Update();
		void Render() const;

		void SetGame(Game* game);

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < GameObject*> m_Objects{};

		static unsigned int m_IdCounter;
		Game* m_Game;
	};
}
