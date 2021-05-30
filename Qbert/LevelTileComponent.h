#pragma once
#include <Component.h>
#include <iostream>
//#include "GameObject.h"

namespace dae {
	class RenderComponent;
}

//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/glm.hpp>
//#pragma warning(pop)
//class GameObject;

class LevelTileComponent : public dae::Component
{
public:
	LevelTileComponent(dae::GameObject* pOwner);
	~LevelTileComponent() override = default;

	void Update() override;
	void SetTile(const std::string& filename);
	void SetPosition(const float x, const float y);

private:
	dae::RenderComponent* m_Tile;
	//glm::vec3 m_ActiveColor{ 255,255,255 };
};
