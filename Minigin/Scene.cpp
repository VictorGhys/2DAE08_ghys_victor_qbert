#include "MiniginPCH.h"
#include "Scene.h"

#include "Game.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto object : m_Objects)
	{
		delete object;
	}
	delete m_Game;
};

void Scene::Add(GameObject* pObject)
{
	m_Objects.push_back(pObject);
}
void Scene::Remove(GameObject* object)
{
	auto It = std::find(m_Objects.begin(), m_Objects.end(), object);
	if (It == m_Objects.end())
		return;
	m_Objects.erase(It);
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object->Update();
	}
	if (m_Game)
		m_Game->Update();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		for (RenderComponent* renderComponent : object->GetComponentsByType<RenderComponent>())
		{
			renderComponent->Render();
		}
	}
	m_Game->Render();
}
void Scene::SetGame(Game* game)
{
	m_Game = game;
}

void Scene::ResetGame()
{
	delete m_Game;
	m_Game = nullptr;
}

void Scene::Destroy(GameObject* object)
{
	Remove(object);
	delete object;
	object = nullptr;
}