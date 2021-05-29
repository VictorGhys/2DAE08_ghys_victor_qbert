#include "MiniginPCH.h"
#include "GameTime.h"

dae::GameTime* dae::GameTime::m_Instance = nullptr;

dae::GameTime* dae::GameTime::GetInstance()
{
	if (m_Instance != nullptr)
	{
		return m_Instance;
	}
	m_Instance = new GameTime();
	return m_Instance;
}
float dae::GameTime::GetFPS() const
{
	return roundf(1 / m_DeltaTime);
}
float dae::GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
void dae::GameTime::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}
void dae::GameTime::Destroy()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}