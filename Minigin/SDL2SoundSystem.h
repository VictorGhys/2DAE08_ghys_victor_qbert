#pragma once
#include <condition_variable>
#include <queue>
#include <thread>
#include "SoundSystem.h"
namespace dae
{
	class SDL2SoundSystem : public SoundSystem
	{
	public:
		SDL2SoundSystem();
		virtual ~SDL2SoundSystem();
		SDL2SoundSystem(const SDL2SoundSystem&) = delete;
		SDL2SoundSystem& operator=(const SDL2SoundSystem&) = delete;
		SDL2SoundSystem(SDL2SoundSystem&&) = delete;
		SDL2SoundSystem& operator=(SDL2SoundSystem&&) = delete;

		void Play(const std::string& path, const int volume) override;
		void ToggleMute() override;
	private:
		void Update();

		struct Sound
		{
			const std::string& path;
			const int volume;
		};

		std::thread m_Thread;
		bool m_IsMuted;
		std::atomic_bool m_IsPlaying;
		std::condition_variable m_ActiveCondition;	//condition to not waste cpu cycles
		std::queue<Sound> m_SoundQueue;
		std::mutex m_Mutex;
	};
}
