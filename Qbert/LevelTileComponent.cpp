#include "MiniginPCH.h"
#include "LevelTileComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

LevelTileComponent::LevelTileComponent(dae::GameObject* pOwner)
	:Component(pOwner)
{
	m_Tile = new dae::RenderComponent(pOwner);
	pOwner->AddComponent(m_Tile);
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
	m_Tile->SetPosition(x, y);
}