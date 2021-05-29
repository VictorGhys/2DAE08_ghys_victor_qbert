#include "MiniginPCH.h"
#include "Component.h"

dae::Component::Component(GameObject* pOwner)
	:m_pOwner(pOwner)
{
	
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}
