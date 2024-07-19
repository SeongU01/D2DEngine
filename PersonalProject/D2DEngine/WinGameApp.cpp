#include "pch.h"
#include "WinGameApp.h"
#ifndef NDEBUG
#include "../D2DEngine/DebugConsole.h"
#endif // !NDEBUG
WinGameApp* WinGameApp::pInstance = nullptr;
HWND WinGameApp::hWnd;

LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return WinGameApp::pInstance->WndProc(hWnd, message, wParam, lParam);
}

WinGameApp::WinGameApp(HINSTANCE hInstance)
	:hInstance(hInstance), szTitle(L"Solar System"), szWindowClass(L"WinGameApp")
	, clientSize({ 0,0 })
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());


	WinGameApp::pInstance = this;
	wc.hInstance = hInstance;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefaultWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = szWindowClass;


}

WinGameApp::~WinGameApp()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
}

bool WinGameApp::Initialize(UINT width, UINT height)
{
#ifndef NDEBUG
	Debug.Get_Console();
#endif // !NDEBUG
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.
	clientSize.width = width;
	clientSize.height = height;

	//윈도우 등록
	RegisterClassExW(&wc);

	pRenderer = std::make_shared<D2DRenderer>();
	pRenderer->SetClientSize(width, height);

	//원하는 크기가 조정되어서 리턴됨
	RECT rcClient = { 0,0,clientSize.width,clientSize.height };
	//AdjustWindowRect(&rcClient, WS_OVERLAPPED, FALSE);

	//윈도우 생성
	hWnd = CreateWindowW(
		szWindowClass,
		szTitle, WS_OVERLAPPEDWINDOW,
		startPosX, startPosY,//시작위치
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		nullptr, nullptr, hInstance, nullptr
	);
	if (!hWnd) { return false; }

	//윈도우 보이기
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);


	// Direct2D초기화를 작성한다.
	pRenderer->Initialize(hWnd);

	//ResourceManager 시작.
	ResourceManager::Create(pRenderer);
	//timer 초기화
	Timer::InitTimer();

	//input 초기화
	Input::inputManager->InitInput(hWnd, clientSize);

	return true;
} 

void WinGameApp::Run()
{
	prevTime = (float)Timer::GetTick();
	currTime = 0.0;
	deltaTime = 0.0;

	// 공통으로 사용하는 윈도우 게임 루프를 작성한다.
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);

		}
		else
		{
			currTime = Timer::GetTick();
			deltaTime = currTime - prevTime;
			prevTime = currTime;
			Update(deltaTime);
			Render();
		}
	}

}

void WinGameApp::OnResume() 
{
	prevTime = (float)Timer::GetTick();
}

void WinGameApp::Uninitialize()
{
#ifndef NDEBUG
	Debug.Close_Console();
#endif // !NDEBUG

	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
	// Direct2D 해제를 호출한다.

	//D2DRenderer::pInstance->Uninitialize();
	ResourceManager::Destroy();
	Input::inputManager->DestroyInsatance();
	pRenderer->Uninitialize();
}

void WinGameApp::Update(float dt)
{
	Input::inputManager->Update();
	CalculateFrameStats(dt);
	//Debug.Log((int)pRenderer->GetUsedVRAM());
}

void WinGameApp::CalculateFrameStats(float dt)
{
	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if (frameCnt == 0)
		return;

	timeElapsed += dt;

	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCnt;  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame

		std::wstring windowText;
		windowText.append(szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		windowText.append(L" Used VRAM: ");
		windowText.append(std::to_wstring(pRenderer->GetUsedVRAM()));
		windowText.append(L"KB");

		SetWindowText(hWnd, windowText.c_str());

		//다음 계산을위해 리셋
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}

LRESULT WinGameApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ENTERSIZEMOVE:
		OnResume();
		break;
	case WM_EXITSIZEMOVE:
		OnResume();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
