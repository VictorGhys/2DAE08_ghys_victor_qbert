#pragma once
#include "Component.h"

namespace dae
{
	class QbertObserver;

	class QbertComponent : public Component
	{
	public:
		QbertComponent(GameObject* pOwner);
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
