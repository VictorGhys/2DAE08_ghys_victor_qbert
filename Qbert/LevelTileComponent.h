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
	class QbertComponent;

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
		LevelTileComponent(dae::GameObject* pOwner, TileType type, float xpos, float ypos, QbertComponent* qbertComponent);
		~LevelTileComponent() override = default;

		void Update() override;
		void SetTile(const std::string& filename) const;
		void SetPosition(float x, float y) const;
		TileType GetTileType() const { return m_Type; }
		void ChangeColor();
		static int m_ActiveTiles;
	private:
		dae::RenderComponent* m_Tile;
		TileType m_Type;
		int m_ActiveLevel;
		std::vector<std::string> m_ActiveLevels;
		QbertComponent* m_QbertComponent;
	};
}
