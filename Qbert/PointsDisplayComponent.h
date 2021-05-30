#pragma once
#include "Component.h"
#include "QbertObserver.h"

namespace dae
{
	class QbertComponent;
	class TextComponent;
	class Font;

	class PointsDisplayComponent : public Component, public QbertObserver
	{
	public:
		PointsDisplayComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font);
		~PointsDisplayComponent();
		void Update() override;
		void SetPosition(float x, float y);
		void SetQbert(QbertComponent* qbert);
		void ChangedTile() override;
		void Died() override{};
	private:
		TextComponent* m_pTextComponent;
		int m_Points;
		QbertComponent* m_Player;
	};
	;
}

