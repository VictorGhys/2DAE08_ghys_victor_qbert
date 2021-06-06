#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

dae::NullSoundSystem dae::ServiceLocator::m_DefaultSoundSystem;
dae::SoundSystem* dae::ServiceLocator::m_SoundSystemInstance = &m_DefaultSoundSystem;

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystemInstance;
}
void dae::ServiceLocator::RegisterSoundSystem(SoundSystem* ss)
{
	m_SoundSystemInstance = ss == nullptr ? &m_DefaultSoundSystem : ss;
}
void dae::ServiceLocator::DeRegisterSoundSystem()
{
	delete m_SoundSystemInstance;
}