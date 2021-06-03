#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class Font;
	class TextComponent;
}
namespace qbert
{
	class QbertComponent;

	class HealthDisplayComponent : public dae::Component, public QbertObserver
	{
	public:
		HealthDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font, const std::string& header = "Lives: ");
		~HealthDisplayComponent() = default;
		void Update() override;
		void SetPosition(float x, float y) const;
		void SetQbert(QbertComponent* qbert);
		void ChangedTile() override {}
		void RemainingDisk() override {}
		void DefeatCoily() override {}
		void CatchSlickOrSlam() override {}
		void Died() override;
	private:
		void SetHealth(const std::string& text) const;
		dae::TextComponent* m_pTextComponent;
		QbertComponent* m_Player;
		std::string m_Header;
	};
}
