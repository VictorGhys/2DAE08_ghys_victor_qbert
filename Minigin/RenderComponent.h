#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae {
	class GameObject;
	class Texture2D;
	class RenderComponent : public dae::Component
	{
	public:
		explicit RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
		
		void Update() override;
		void Render() const;
		std::shared_ptr<dae::Texture2D> GetTexture() const;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);
		void SetPosition(float x, float y);

	private:
		std::shared_ptr<dae::Texture2D> m_pTexture{};
		Transform m_Transform;
	};
}
