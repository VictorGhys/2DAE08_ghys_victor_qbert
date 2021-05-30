#include "MiniginPCH.h"
#include "HealthDisplayComponent.h"


#include "GameObject.h"
#include "TextComponent.h"
#include "QbertComponent.h"

dae::HealthDisplayComponent::HealthDisplayComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	:Component(pOwner),
	m_pTextComponent(new TextComponent(pOwner, text, font))
{
	pOwner->AddComponent(m_pTextComponent);
	if (m_Player != nullptr)
	{
		m_Player->AddObserver(this);
	}
}
dae::HealthDisplayComponent::~HealthDisplayComponent()
{
	
}
void dae::HealthDisplayComponent::Died()
{
	m_pTextComponent->SetText(std::to_string(m_Player->GetHealth()));
}
void dae::HealthDisplayComponent::SetQbert(QbertComponent* qbert)
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
	m_pTextComponent->SetText(std::to_string(m_Player->GetHealth()));
}

void dae::HealthDisplayComponent::Update()
{
	
}

void dae::HealthDisplayComponent::SetPosition(const float x, const float y)
{
	m_pTextComponent->SetPosition(x, y);
}