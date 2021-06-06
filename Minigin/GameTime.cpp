#include "MiniginPCH.h"
#include "GameTime.h"

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