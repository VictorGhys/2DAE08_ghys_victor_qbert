#include "MiniginPCH.h"
#include "TextComponent.h"

#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	:Component(pOwner),
	m_NeedsUpdate(true),
	m_Text(text),
	m_Font(font),
	m_pRenderComponent(new RenderComponent(pOwner))
{
	pOwner->AddComponent(m_pRenderComponent);
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	m_pRenderComponent->Render();
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	//m_Transform.SetPosition(x, y, 0.0f);
	m_pRenderComponent->SetPosition(x, y);
}
dae::TextComponent::~TextComponent()
{
	m_Font.reset();
}


