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

	// ������ Ŭ���� �غ��ϴ� �۾��� �ٸ� �Լ��� ����� ���� �ʾ� �����ڿ��� �Ѵ�.
	// �������Ͽ� ������ ������ �������� DemoApp�� ���� �������̳� ���ڸ� ������ ������ Ŭ���� ������ �غ��Ѵ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_IWBM, szWindowClass, MAX_LOADSTRING);
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IWBM));
	//m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);                  //�����̹Ƿ� �޴��� ���ش�
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
	__super::Initialize(width, height);	 // ������ ���� , Direct2D �ʱ�ȭ
	
	
	
	//�� ������ֱ�
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
