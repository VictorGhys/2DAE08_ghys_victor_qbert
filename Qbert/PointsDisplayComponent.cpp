#include "MiniginPCH.h"
#include "PointsDisplayComponent.h"


#include "GameObject.h"
#include "QbertComponent.h"
#include "TextComponent.h"

dae::PointsDisplayComponent::PointsDisplayComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	:Component(pOwner),
	m_pTextComponent(new TextComponent(pOwner, text, font))
{
	pOwner->AddComponent(m_pTextComponent);
}

dae::PointsDisplayComponent::~PointsDisplayComponent()
{
	
}

void dae::PointsDisplayComponent::SetQbert(QbertComponent* qbert)
{
	if (m_Player != nullptr)
	{
		m_Player->RemoveObserver(this);
	}
	m_Player = qbert;
	m_Points = 0;
	if (m_Player != nullptr)
	{
		m_Player->AddObserver(this);
	}
	m_pTextComponent->SetText(std::to_string(m_Points));
}

void dae::PointsDisplayComponent::ChangedTile()
{
	m_Points += 25;
	m_pTextComponent->SetText(std::to_string(m_Points));

}

void dae::PointsDisplayComponent::Update()
{

}

void dae::PointsDisplayComponent::SetPosition(const float x, const float y)
{
	m_pTextComponent->SetPosition(x, y);
}