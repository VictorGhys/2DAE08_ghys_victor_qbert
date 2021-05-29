#pragma once
#include "SoundSystem.h"
namespace dae
{
	class LoggingSoundSystem : public SoundSystem
	{
	public:
		LoggingSoundSystem(SoundSystem* ss);
		void Play(const std::string& path, const int volume) override;
		void ToggleMute() override;
	private:
		SoundSystem* m_pRealSoundSystem;
		bool m_IsMuted;
	};
}