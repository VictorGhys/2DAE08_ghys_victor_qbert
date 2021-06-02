#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class TextComponent;
	class Font;
}
namespace qbert
{
	class QbertComponent;

	class PointsDisplayComponent : public dae::Component, public QbertObserver
	{
	public:
		PointsDisplayComponent(dae::GameObject* pOwner, const std::string& text, const std::shared_ptr<dae::Font>& font);
		~PointsDisplayComponent();
		void Update() override;
		void SetPosition(float x, float y);
		void SetQbert(QbertComponent* qbert);
		void ChangedTile() override;
		void Died() override {};
	private:
		dae::TextComponent* m_pTextComponent;
		int m_Points;
		QbertComponent* m_Player;
	};
	;
}
