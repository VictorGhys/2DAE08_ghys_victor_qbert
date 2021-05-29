#pragma once
using sound_id = unsigned short;
namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string& path, const int volume) = 0;
		virtual void ToggleMute() = 0;

		SoundSystem() = default;
		SoundSystem(const SoundSystem&) = delete;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator=(SoundSystem&&) = delete;
	};


	class NullSoundSystem final : public SoundSystem
	{
		void Play(const std::string&, const int) override {}
		void ToggleMute() override {}
	};
}