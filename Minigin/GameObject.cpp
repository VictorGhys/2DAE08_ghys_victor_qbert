#include "MiniginPCH.h"
#include "GameObject.h"
#include "algorithm"
#include "Component.h"
#include "Transform.h"

dae::GameObject::GameObject()
	:m_pTransform(new Transform())
{
}

void dae::GameObject::Update()
{
	for (auto component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);
}
void dae::GameObject::AddComponent(Component* pComponent)
{
	m_Components.push_back(pComponent);
}

dae::Transform* dae::GameObject::GetTransform() const
{
	return m_pTransform;
}
//void dae::GameObject::SetTransform(const Transform& transform)
//{
//	m_pTransform = transform;
//}
dae::GameObject::~GameObject()
{
	for (auto component : m_Components)
	{
		delete component;
	}
	delete m_pTransform;
}