#pragma once
namespace qbert
{
	class HealthComponent
	{
	public:
		HealthComponent(int lives);
		virtual void Kill() = 0;
		int GetHealth() const { return m_Health; }
	protected:
		int m_Health;
	};
}