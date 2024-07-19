// Animation.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//


#include "pch.h"
#include "IWBM.h"
#include "IWBMApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  //_CrtSetBreakAlloc(352);
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //GameApp App(hInstance, nCmdShow);   // 기본클래스도 윈도우 생성,메시지 루프 잘작동한다.
  IWBMApp App(hInstance);  // 생성자에서 아이콘,윈도우 이름만 바꾼다

  App.Initialize(1400, 1000);
  App.Run();
  App.Uninitialize();
}