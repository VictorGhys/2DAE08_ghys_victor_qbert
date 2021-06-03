#include "MiniginPCH.h"
#include "LevelTileComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "QbertGame.h"

int qbert::LevelTileComponent::m_ActiveTiles = 0;

qbert::LevelTileComponent::LevelTileComponent(dae::GameObject* pOwner, TileType type, float xpos, float ypos)
	:Component(pOwner),
	m_Tile(new dae::RenderComponent(pOwner)),
	m_Type(type)
{
	m_ActiveLevels.push_back("../Data/Tile1.png");
	m_ActiveLevels.push_back("../Data/Tile2.png");
	m_ActiveLevels.push_back("../Data/Tile3.png");

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
		//m_Tile->SetPosition(m_Tile->GetPosition().x + 15.f, m_Tile->GetPosition().y - 20.f);
		m_Tile->SetPosition(m_Tile->GetPosition().x + 15.f, m_Tile->GetPosition().y + 30.f);
		break;
	default:
		break;
	}
}
void qbert::LevelTileComponent::Update()
{
}

void qbert::LevelTileComponent::SetTile(const std::string& filename) const
{
	m_Tile->SetTexture(filename);
}
void qbert::LevelTileComponent::SetPosition(float x, float y) const
{
	//m_Tile->SetPosition(x, y);
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
		}
		break;
	case TileType::DOUBLE_TILE:
		if (m_ActiveLevel < 2)
		{
			m_ActiveLevel++;
			m_Tile->SetTexture(m_ActiveLevels.at(m_ActiveLevel));
			m_ActiveTiles++;
		}
		break;
	case TileType::REVERTABLE:
		if (m_ActiveLevel == 0)
		{
			m_ActiveLevel++;
			m_ActiveTiles++;
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

	if (m_ActiveTiles >= QbertGame::m_TilesActiveToWin)
	{
	}
}