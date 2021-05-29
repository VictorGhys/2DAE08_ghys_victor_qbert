#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class QbertComponent;
	class Font;
	class TextComponent;

	class HealthDisplayComponent : public dae::Component, public QbertObserver
	{
	public:
		HealthDisplayComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font);
		~HealthDisplayComponent();
		void Update() override;
		void SetPosition(float x, float y);
		void SetQbert(QbertComponent* qbert);
		void ChangedTile() override{};
		void Died() override;
	private:
		TextComponent* m_pTextComponent;
		QbertComponent* m_Player;
	};

}
