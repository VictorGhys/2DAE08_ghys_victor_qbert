#include "MiniginPCH.h"
#include "LevelTileComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "QbertComponent.h"

int qbert::LevelTileComponent::m_ActiveTiles = 0;

qbert::LevelTileComponent::LevelTileComponent(dae::GameObject* pOwner, TileType type, float xpos, float ypos, QbertComponent* qbertComponent)
	:Component(pOwner),
	m_Tile(new dae::RenderComponent(pOwner)),
	m_Type(type),
	m_ActiveLevel(),
	m_ActiveLevels({ "../Data/Tile1.png", "../Data/Tile2.png", "../Data/Tile3.png" }),
	m_QbertComponent(qbertComponent)
{
	pOwner->AddComponent(m_Tile);
	SetPosition(xpos, ypos);

	switch (m_Type)
	{
	case TileType::TILE:
		m_Tile->SetTexture(m_ActiveLevels.at(0));
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::DOUBLE_TILE:
		m_Tile->SetTexture(m_ActiveLevels.at(0));
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::REVERTABLE:
		m_Tile->SetTexture(m_ActiveLevels.at(0));
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::DISK:
		m_Tile->SetTexture("../Data/Disk.png");
		m_Tile->SetWidth(32);
		m_Tile->SetHeight(20);
		// set disk on the right position
		m_Tile->SetPosition(m_Tile->GetPosition().x + 15.f, m_Tile->GetPosition().y + 30.f);
		break;
	default:
		break;
	}
}

void qbert::LevelTileComponent::SetTile(const std::string& filename) const
{
	m_Tile->SetTexture(filename);
}
void qbert::LevelTileComponent::SetPosition(float x, float y) const
{
	m_pOwner->GetTransform()->SetPosition(x, y, 0);
}
void qbert::LevelTileComponent::ChangeColor()
{
	switch (m_Type)
	{
	case TileType::TILE:
		if (m_ActiveLevel == 0)
		{
			m_ActiveLevel++;
			m_Tile->SetTexture(m_ActiveLevels.at(m_ActiveLevel));
			m_ActiveTiles++;
			m_QbertComponent->ChangeTile();
		}
		break;
	case TileType::DOUBLE_TILE:
		if (m_ActiveLevel < 2)
		{
			m_ActiveLevel++;
			m_Tile->SetTexture(m_ActiveLevels.at(m_ActiveLevel));
			m_ActiveTiles++;
			m_QbertComponent->ChangeTile();
		}
		break;
	case TileType::REVERTABLE:
		if (m_ActiveLevel == 0)
		{
			m_ActiveLevel++;
			m_ActiveTiles++;
			m_QbertComponent->ChangeTile();
		}
		else
		{
			m_ActiveLevel--;
			m_ActiveTiles--;
		}
		m_Tile->SetTexture(m_ActiveLevels.at(m_ActiveLevel));
		break;
	default:
		break;
	}
}

void qbert::LevelTileComponent::RevertColor()
{
	if (m_ActiveLevel > 0)
	{
		m_ActiveLevel--;
		m_Tile->SetTexture(m_ActiveLevels.at(m_ActiveLevel));
		m_ActiveTiles--;
	}
}