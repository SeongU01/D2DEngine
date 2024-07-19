#include "pch.h"
#include "InputSystem.h"
#include "WinGameApp.h"

namespace Input
{
	InputSystem* InputSystem::_sInstance = nullptr;
	InputSystem* inputManager = InputSystem::GetInstance();

	InputSystem::~InputSystem()
	{
	}

	void InputSystem::InitInput(HWND hWnd,D2D_SIZE_U& clientSize)
	{
		_hWnd = hWnd;
		_width = clientSize.width;
		_height =clientSize.height;

		_mouseClient.x = _width / 2;
		_mouseClient.y = _height / 2;
		SetCursorPos(_mouseClient.x, _mouseClient.y);
	}

	void InputSystem::ReleaseInput()
	{
	}

	void InputSystem::Update()
	{
		GetCursorPos(&_mouseClient);
		//std::cout << _mouseClient.x << ", " << _mouseClient.y << std::endl;
		ScreenToClient(_hWnd, &_mouseClient);
		//key상태 변경
		bool ret = GetKeyboardState((PBYTE)&_byKeyCurr);

		for (int i = 0; i < KEYBOARD_MAX; i++)
		{
			_byKeyTurnUp[i] = (_byKeyPrev[i] ^ _byKeyCurr[i]) & _byKeyPrev[i];
			_byKeyTurnDn[i] = (_byKeyPrev[i] ^ _byKeyCurr[i]) & _byKeyCurr[i];
		}

		memcpy(&_byKeyPrev, &_byKeyCurr, KEYBOARD_MAX);
	}


	BOOL InputSystem::IsTurnDn(BYTE vk)
	{
		if (_byKeyTurnDn[vk] & 0x80)
			return TRUE;

		return FALSE;
	}


	BOOL InputSystem::IsTurnUp(BYTE vk)
	{
		if (_byKeyTurnUp[vk] & 0x80)
			return TRUE;

		return FALSE;
	}


	BOOL InputSystem::IsCurrDn(BYTE vk)
	{
		if (_byKeyCurr[vk] & 0x80)
			return TRUE;

		return FALSE;
	}


	BOOL InputSystem::IsCurrUp(BYTE vk)
	{
		if (_byKeyCurr[vk] & 0x80)
			return FALSE;

		return TRUE;
	}


	POINT InputSystem::GetMouseClient()
	{
		return _mouseClient;
	}

	InputSystem* InputSystem::GetInstance()
	{
		if (_sInstance == nullptr)
		{
			_sInstance = new InputSystem;
		}
		return _sInstance;
	}

	void InputSystem::DestroyInsatance()
	{
		delete _sInstance;
		_sInstance = nullptr;
	}
}
