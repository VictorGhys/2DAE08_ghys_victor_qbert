#pragma once
#include "SoundSystem.h"
namespace dae
{
	class ServiceLocator final
	{
		static SoundSystem* m_SoundSystemInstance;
		static NullSoundSystem m_DefaultSoundSystem;
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(SoundSystem* ss);
	};
}