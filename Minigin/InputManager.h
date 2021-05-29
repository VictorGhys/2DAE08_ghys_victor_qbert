#pragma once
#include <map>
#include <utility>
#include <Windows.h>
#include <Xinput.h>
#include "Command.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton : WORD
	{
		//for keystate
		/*ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y*/

		//for keystroke
		ButtonA = VK_PAD_A,
		ButtonB = VK_PAD_B,
		ButtonX = VK_PAD_X,
		ButtonY = VK_PAD_Y,
		ButtonRB = VK_PAD_RSHOULDER,
		ButtonLB = VK_PAD_LSHOULDER,
		ButtonRT = VK_PAD_RTRIGGER,
		ButtonLT = VK_PAD_LTRIGGER,
		ButtonUP = VK_PAD_DPAD_UP,
		ButtonDOWN = VK_PAD_DPAD_DOWN,
		ButtonLEFT = VK_PAD_DPAD_LEFT,
		ButtonRIGHT = VK_PAD_DPAD_RIGHT,
		ButtonSTART = VK_PAD_START
		//todo: add the other buttons
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void BindCommand(ControllerButton button, Command* command);
	private:
		XINPUT_STATE m_CurrentState;
		XINPUT_KEYSTROKE m_CurrentKeyStroke{};
		using ControllerCommandsMap = std::map<ControllerButton, Command*>;
		ControllerCommandsMap m_ConsoleCommands{};
		WORD m_KeystrokeMode{XINPUT_KEYSTROKE_KEYDOWN};
	};
}
