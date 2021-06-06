#pragma once
#include "Component.h"
#include "HealthComponent.h"

namespace qbert
{
	class QbertGame;
	class QbertObserver;

	class QbertComponent : public dae::Component, public HealthComponent
	{
	public:
		QbertComponent(dae::GameObject* pOwner, qbert::QbertGame* qbertGame);
		~QbertComponent() = default;
		void Kill() override;
		void Update() override;
		void ChangeTile();
		void DefeatCoily();
		void CatchSlickOrSlam();
		void RemainingDisk();
		void AddObserver(QbertObserver* observer);
		void RemoveObserver(QbertObserver* observer);

	private:
		std::vector<QbertObserver*> m_Observers;
		QbertGame* m_QbertGame;
	};
}
