#include "pch.h"
#include "IWBMApp.h"
#include "SceneManager.h"

IWBMApp::IWBMApp(HINSTANCE hInstance)
	:
	WinGameApp::WinGameApp(hInstance)
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

	// 윈도우 클래스 준비하는 작업을 다른 함수로 만들고 싶지 않아 생성자에서 한다.
	// 실행파일에 합쳐진 데이터 영역에서 DemoApp에 관한 아이콘이나 문자를 가져와 윈도우 클래스 정보를 준비한다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_IWBM, szWindowClass, MAX_LOADSTRING);
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IWBM));
	//m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);                  //게임이므로 메뉴는 없앤다
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IWBM));

	_SceneGraph = new SceneManager;
}

IWBMApp::~IWBMApp()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

}

bool IWBMApp::Initialize(UINT width, UINT height)
{
	SetStartWindowPos(100, 100);
	__super::Initialize(width, height);	 // 윈도우 생성 , Direct2D 초기화
	
	
	
	//씬 등록해주기
	_SceneGraph->RegisterScene(pRenderer);

	return true;
}

void IWBMApp::Update(float dt)
{
	__super::Update(dt);

	_SceneGraph->GetCurrentScene()->Update(dt);

}

void IWBMApp::Render()
{
	pRenderer->GetRenderTarget()->BeginDraw();
	pRenderer->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	_SceneGraph->GetCurrentScene()->Render(pRenderer->GetRenderTarget());


	pRenderer->GetRenderTarget()->EndDraw();
}

void IWBMApp::Uninitialize()
{
	delete _SceneGraph;
	WinGameApp::Uninitialize();
}
