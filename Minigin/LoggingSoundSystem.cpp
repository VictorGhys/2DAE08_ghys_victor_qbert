#include "MiniginPCH.h"
#include "LoggingSoundSystem.h"

dae::LoggingSoundSystem::LoggingSoundSystem(SoundSystem* ss)
	:m_pRealSoundSystem(ss),
	m_IsMuted(false)
{
}

dae::LoggingSoundSystem::~LoggingSoundSystem()
{
	delete m_pRealSoundSystem;
}

void dae::LoggingSoundSystem::Play(const std::string& path, const int volume)
{
	if (!m_IsMuted)
	{
		m_pRealSoundSystem->Play(path, volume);
	}
	std::cout << "playing " << path << " at volume " << volume << std::endl;
}

void dae::LoggingSoundSystem::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
	m_pRealSoundSystem->ToggleMute();
	std::cout << "toggled mute\n";
}