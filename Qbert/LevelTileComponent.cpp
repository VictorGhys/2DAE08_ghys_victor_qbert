#include "MiniginPCH.h"
#include "LevelTileComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

LevelTileComponent::LevelTileComponent(dae::GameObject* pOwner, TileType type, float xpos, float ypos)
	:Component(pOwner),
	m_Tile(new dae::RenderComponent(pOwner)),
	m_Type(type)
{
	pOwner->AddComponent(m_Tile);
	SetPosition(xpos, ypos);

	switch (m_Type)
	{
	case TileType::TILE:
		m_Tile->SetTexture("../Data/Tile1.png");
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::DOUBLE_TILE:
		m_Tile->SetTexture("../Data/Tile1.png");
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::REVERTABLE:
		m_Tile->SetTexture("../Data/Tile1.png");
		m_Tile->SetWidth(64);
		m_Tile->SetHeight(64);
		break;
	case TileType::DISK:
		m_Tile->SetTexture("../Data/Disk.png");
		m_Tile->SetWidth(32);
		m_Tile->SetHeight(20);
		// set disk on the right position
		m_Tile->SetPosition(m_Tile->GetPosition().x + 15.f, m_Tile->GetPosition().y - 20.f);
		break;
	default:
		break;
	}
}
void LevelTileComponent::Update()
{
}

void LevelTileComponent::SetTile(const std::string& filename)
{
	m_Tile->SetTexture(filename);
}
void LevelTileComponent::SetPosition(const float x, const float y)
{
	//m_Tile->SetPosition(x, y);

	m_pOwner->GetTransform()->SetPosition(x, y, 0);
}