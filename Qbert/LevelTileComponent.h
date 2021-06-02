#pragma once
#include <Component.h>
#include <iostream>
//#include "GameObject.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dae {
	class RenderComponent;
}

//#pragma warning(push)
//#pragma warning (disable:4201)
//#include <glm/glm.hpp>
//#pragma warning(pop)
//class GameObject;
namespace qbert
{
	class LevelTileComponent : public dae::Component
	{
	public:
		enum class TileType : char
		{
			TILE = 'T',
			DOUBLE_TILE = '2',
			REVERTABLE = 'R',
			DISK = 'D',
			DEATH = '.'
		};
		LevelTileComponent(dae::GameObject* pOwner, TileType type, float xpos, float ypos);
		~LevelTileComponent() override = default;

		void Update() override;
		void SetTile(const std::string& filename);
		void SetPosition(const float x, const float y);
		TileType GetTileType() const { return m_Type; }
	private:
		dae::RenderComponent* m_Tile;
		TileType m_Type;
		//glm::vec3 m_ActiveColor{ 255,255,255 };
	};
}
