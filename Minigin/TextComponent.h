#pragma once
#include "Component.h"
#include "Transform.h"
#include "RenderComponent.h"

namespace dae {
	class Font;
	class Texture2D;
	class TextComponent :
		public Component
	{
	public:
		void Update() override;
		void Render() const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent();
		TextComponent(const TextComponent & other) = delete;
		TextComponent(TextComponent && other) = delete;
		TextComponent& operator=(const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent && other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		RenderComponent* m_pRenderComponent;
	};
}
