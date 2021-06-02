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
		HealthDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font);
		~HealthDisplayComponent();
		void Update() override;
		void SetPosition(float x, float y);
		void SetQbert(QbertComponent* qbert);
		void ChangedTile() override {};
		void Died() override;
	private:
		dae::TextComponent* m_pTextComponent;
		QbertComponent* m_Player;
	};
}
