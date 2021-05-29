#include "MiniginPCH.h"
#include "FPSComponent.h"


#include "GameObject.h"
#include "GameTime.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	:Component(pOwner),
	m_pTextComponent(new TextComponent(pOwner, text, font))
{
	pOwner->AddComponent(m_pTextComponent);
}
void dae::FPSComponent::Update()
{
	float fps = GameTime::GetInstance()->GetFPS();
	if (fps != m_FPS)
	{
		m_pTextComponent->SetText(std::to_string(fps).substr(0, 3) + "FPS");
		m_FPS = fps;
	}
}


