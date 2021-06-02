#pragma once
#include "Transform.h"
#include "SceneObject.h"

namespace dae
{
	class Component;
	class GameObject final
	{
	public:
		void Update();

		template <typename ComponentType>
		ComponentType* GetComponentByType() const
		{
			auto compIt = std::find_if(m_Components.begin(), m_Components.end(),
				[](Component* pComp)
				{
					return dynamic_cast<const ComponentType*>(pComp) != nullptr;
				});
			if (compIt == m_Components.end())
			{
				return nullptr;
			}
			return static_cast<ComponentType*>(*compIt);
		}
		template <typename ComponentType>
		std::vector<ComponentType*> GetComponentsByType() const
		{
			std::vector<ComponentType*> result;
			auto compIt = std::find_if(m_Components.begin(), m_Components.end(),
				[](Component* pComp)
				{
					return dynamic_cast<const ComponentType*>(pComp) != nullptr;
				});
			// continue looping until you are at the end
			while (compIt != m_Components.end())
			{
				result.push_back(static_cast<ComponentType*>(*compIt));
				compIt = std::find_if(compIt + 1, m_Components.end(),
					[](Component* pComp)
					{
						return dynamic_cast<const ComponentType*>(pComp) != nullptr;
					});
			}
			return result;
		}

		void SetPosition(float x, float y);
		void AddComponent(Component* pComponent);
		Transform* GetTransform() const;
		//void SetTransform(const Transform& transform);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform* m_pTransform;
		std::vector<Component*> m_Components;
	};
}
