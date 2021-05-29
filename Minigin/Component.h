#pragma once
namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual void Update() = 0;
		GameObject* GetOwner() const;
		
		Component(GameObject* pOwner);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	protected:
		GameObject* m_pOwner;
	};
}
