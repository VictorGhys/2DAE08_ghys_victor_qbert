#pragma once
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public Component
	{
	public:
		explicit FPSComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent & other) = delete;
		FPSComponent(FPSComponent && other) = delete;
		FPSComponent& operator=(const FPSComponent & other) = delete;
		FPSComponent& operator=(FPSComponent && other) = delete;

		void Update() override;
	private:
		TextComponent* m_pTextComponent;
		float m_FPS;
	};
}


