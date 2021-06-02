#include "MiniginPCH.h"
#include "PointsDisplayComponent.h"

#include "GameObject.h"
#include "QbertComponent.h"
#include "TextComponent.h"

qbert::PointsDisplayComponent::PointsDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font, const std::string& header)
	:Component(pOwner),
	m_pTextComponent(new dae::TextComponent(pOwner, text, font)),
	m_Header(header)
{
	pOwner->AddComponent(m_pTextComponent);
}

qbert::PointsDisplayComponent::~PointsDisplayComponent()
{
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
	m_pTextComponent->SetText(std::to_string(m_Points));
}

void qbert::PointsDisplayComponent::Update()
{
}

void qbert::PointsDisplayComponent::SetPosition(const float x, const float y)
{
	m_pTextComponent->SetPosition(x, y);
}
void qbert::PointsDisplayComponent::SetPoints(const std::string& text)
{
	m_pTextComponent->SetText(m_Header + text);
}