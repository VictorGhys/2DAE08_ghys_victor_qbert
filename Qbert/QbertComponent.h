#pragma once
#include "Component.h"

namespace qbert
{
	class QbertObserver;

	class QbertComponent : public dae::Component
	{
	public:
		QbertComponent(dae::GameObject* pOwner);
		~QbertComponent() = default;
		void Kill();
		void Update() override;
		int GetHealth() const;
		void ChangeTile();
		void RemainingDisk();
		void AddObserver(QbertObserver* observer);
		void RemoveObserver(QbertObserver* observer);

	private:
		std::vector<QbertObserver*> m_Observers;
		int m_Health;
	};
}
