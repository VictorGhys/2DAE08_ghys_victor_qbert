#pragma once
#include "Component.h"

namespace qbert
{
	class QbertObserver;

	class QbertComponent : public dae::Component
	{
	public:
		QbertComponent(dae::GameObject* pOwner);
		~QbertComponent();
		void Kill();
		void Update() override;
		int GetHealth() const;
		void ChangeTile();
		void AddObserver(QbertObserver* observer);
		void RemoveObserver(QbertObserver* observer);

	private:
		std::vector<QbertObserver*> m_Observers;
		int m_Health;
	};
}
