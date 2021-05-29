#pragma once
namespace dae
{
		
	class GameTime
	{
	public:
		static GameTime* GetInstance();
		float GetFPS() const;
		float GetDeltaTime() const;
		void SetDeltaTime(float deltaTime);
		void Destroy();
	private:
		static GameTime* m_Instance;
		float m_DeltaTime;
	};

}
