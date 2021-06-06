#pragma once
#include "Singleton.h"

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		float GetFPS() const;
		float GetDeltaTime() const;
		void SetDeltaTime(float deltaTime);
	private:
		float m_DeltaTime{};
	};
}
