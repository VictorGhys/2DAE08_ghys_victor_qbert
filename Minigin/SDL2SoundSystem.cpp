#include "MiniginPCH.h"
#include "SDL2SoundSystem.h"
#include "audio.h"

dae::SDL2SoundSystem::SDL2SoundSystem()
	:m_IsMuted(false),
	m_IsPlaying(true)
{
	// Create the dedicated sound thread and let it loop on the update function.
	m_Thread = std::thread([this]()
		{
			this->Update();
		});
}

dae::SDL2SoundSystem::~SDL2SoundSystem()
{
	m_IsPlaying = false;
	m_ActiveCondition.notify_one();
	m_Thread.join();
}

void dae::SDL2SoundSystem::Play(const std::string& path, const int volume)
{
	const Sound sound{ path, volume };
	std::lock_guard<std::mutex> mutexLock{ m_Mutex };
	m_SoundQueue.push(sound);
	m_ActiveCondition.notify_one();
}

void dae::SDL2SoundSystem::Update()
{
	while (m_IsPlaying)
	{
		while (!m_SoundQueue.empty() && !m_IsMuted)
		{
			/*Sound sound = m_SoundQueue.front();
			m_SoundQueue.pop();
			std::unique_lock<std::mutex> mutexLock(m_Mutex);
			playSound(sound.path.c_str(), sound.volume);*/
			std::unique_lock<std::mutex> mutexLock(m_Mutex);
			Sound sound = m_SoundQueue.front();
			m_SoundQueue.pop();
			playSound(sound.path.c_str(), sound.volume);
			mutexLock.unlock();
		}
		std::unique_lock<std::mutex> mLock{ m_Mutex };
		m_ActiveCondition.wait(mLock);
	}
}

void dae::SDL2SoundSystem::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
	if (m_IsMuted)
	{
		pauseAudio();
	}
	else
	{
		unpauseAudio();
	}
}