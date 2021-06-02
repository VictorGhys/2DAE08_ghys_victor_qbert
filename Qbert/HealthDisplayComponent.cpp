#include "MiniginPCH.h"
#include "HealthDisplayComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "QbertComponent.h"

qbert::HealthDisplayComponent::HealthDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font, const std::string& header)
	:Component(pOwner),
	m_pTextComponent(new dae::TextComponent(pOwner, text, font)),
	m_Header(header)
{
	pOwner->AddComponent(m_pTextComponent);
	if (m_Player != nullptr)
	{
		m_Player->AddObserver(this);
	}
}
qbert::HealthDisplayComponent::~HealthDisplayComponent()
{
}
void qbert::HealthDisplayComponent::Died()
{
	SetHealth(std::to_string(m_Player->GetHealth()));
}
void qbert::HealthDisplayComponent::SetQbert(QbertComponent* qbert)
{
	if (m_Player != nullptr)
	{
		m_Player->RemoveObserver(this);
	}
	m_Player = qbert;
	if (m_Player != nullptr)
	{
		m_Player->AddObserver(this);
	}
	SetHealth(std::to_string(m_Player->GetHealth()));
}

void qbert::HealthDisplayComponent::Update()
{
}

void qbert::HealthDisplayComponent::SetPosition(const float x, const float y)
{
	m_pTextComponent->SetPosition(x, y);
}
void qbert::HealthDisplayComponent::SetHealth(const std::string& text)
{
	m_pTextComponent->SetText(m_Header + text);
}