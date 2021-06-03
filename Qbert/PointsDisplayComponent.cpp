#include "MiniginPCH.h"
#include "PointsDisplayComponent.h"

#include "GameObject.h"
#include "QbertComponent.h"
#include "TextComponent.h"

qbert::PointsDisplayComponent::PointsDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font, const std::string& header)
	:Component(pOwner),
	m_pTextComponent(new dae::TextComponent(pOwner, text, font)),
	m_Header(header),
	m_Player(),
	m_Points()
{
	pOwner->AddComponent(m_pTextComponent);
}

void qbert::PointsDisplayComponent::SetQbert(QbertComponent* qbert)
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
	SetPoints(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::ChangedTile()
{
	m_Points += 25;
	SetPoints(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::RemainingDisk()
{
	m_Points += 50;
	SetPoints(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::DefeatCoily()
{
	m_Points += 500;
	SetPoints(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::CatchSlickOrSlam()
{
	m_Points += 300;
	SetPoints(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::Update()
{
}

void qbert::PointsDisplayComponent::SetPosition(const float x, const float y) const
{
	m_pTextComponent->SetPosition(x, y);
}
void qbert::PointsDisplayComponent::SetPoints(const std::string& text) const
{
	m_pTextComponent->SetText(m_Header + text);
}