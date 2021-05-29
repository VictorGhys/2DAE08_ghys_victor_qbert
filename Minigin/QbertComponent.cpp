#include "MiniginPCH.h"
#include "QbertComponent.h"
#include "HealthDisplayComponent.h"
#include "ResourceManager.h"
#include "PointsDisplayComponent.h"
#include "QbertObserver.h"


dae::QbertComponent::QbertComponent(GameObject* pOwner)
	:Component(pOwner),
	m_Health(3)
{
	
}
dae::QbertComponent::~QbertComponent()
{
	
}
void dae::QbertComponent::Update()
{
	
}

void dae::QbertComponent::Kill()
{
	m_Health -= 1;
	std::cout << "qbert died\n";
	for (auto observer : m_Observers)
	{
		observer->Died();
	}
}
void dae::QbertComponent::ChangeTile()
{
	for (auto observer : m_Observers)
	{
		observer->ChangedTile();
	}
}
void dae::QbertComponent::AddObserver(dae::QbertObserver* observer)
{
	m_Observers.push_back(observer);
}
void dae::QbertComponent::RemoveObserver(dae::QbertObserver* observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}


int dae::QbertComponent::GetHealth() const
{
	return m_Health;
}