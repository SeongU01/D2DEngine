#pragma once
#define KEYBOARD_MAX 256

namespace Input
{
	class InputSystem;
	extern InputSystem* inputManager;

	class InputSystem
	{
	private:
		BYTE _byKeyPrev[KEYBOARD_MAX];		// 이전 키의 정보
		BYTE _byKeyCurr[KEYBOARD_MAX];		// 현재 키의 정보
		BYTE _byKeyTurnDn[KEYBOARD_MAX];	// Down된 키의 정보
		BYTE _byKeyTurnUp[KEYBOARD_MAX];   // Up 된 키의 정보

		HWND _hWnd;
		int _width;
		int _height;

		POINT _mouseClient;

		static InputSystem* _sInstance;

		InputSystem() {};
		~InputSystem();
	public:

		/**
	 * @brief 인풋 시스템 초기화
	 */
		void InitInput(HWND hWnd, D2D_SIZE_U& clientSize);
		void ReleaseInput();
		/**
	 * @brief 인풋 관련 업데이트
	 */
		void Update();

		/**
	 * @brief 키가 한번 눌렸는가를 판단
	 * @param vk 판별할 키
	 * @return
	 */
		BOOL IsTurnDn(BYTE vk);

		/**
	 * @brief 키가 한번 때었는가를 판단
	 * @param vk 판별할 키
	 * @return
	 */
		BOOL IsTurnUp(BYTE vk);

		/**
	 * @brief 키가 눌려 있는가를 판단
	 * @param vk 판별할 키
	 * @return
	 */
		BOOL IsCurrDn(BYTE vk);

		/**
	 * @brief 키가 떨어져 있는가를 판단
	 * @param vk 판별할 키
	 * @return
	 */
		BOOL IsCurrUp(BYTE vk);

		/**
	 * @brief 현재 마우스 위치를 반환함
	 * @return 현재 마우스 위치
	 */
		POINT GetMouseClient();

		static InputSystem* GetInstance();
		static void DestroyInsatance();
	};
}

