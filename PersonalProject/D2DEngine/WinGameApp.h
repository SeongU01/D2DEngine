#pragma once
#include "D2DRenderer.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "InputSystem.h"

#define MAX_LOADSTRING 150
class WinGameApp
{
public:
	WinGameApp(HINSTANCE hInstance);
	virtual ~WinGameApp();

	// 자식 클래스가 재정의 가능하도록 virtual keyword 를 붙인다.
	virtual bool Initialize(UINT width, UINT height);
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float dt);
	virtual void Render() = 0;
	static WinGameApp* pInstance;
	static HWND hWnd;

	std::shared_ptr<D2DRenderer>pRenderer;
public:
	HACCEL hAccelTable;
	MSG msg;
	HINSTANCE hInstance;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	WNDCLASSEXW wc;

	int nCmdShow;
	D2D_SIZE_U clientSize;

public:
	void CalculateFrameStats(float dt);
	void OnResume();
	void SetStartWindowPos(float x, float y) { startPosX = x; startPosY = y; };
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);;

private:
	float prevTime;
	float currTime;
	float deltaTime;
	float startPosX=10;
	float startPosY=10;
};

