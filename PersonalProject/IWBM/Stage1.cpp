#include "pch.h"
#include "Stage1.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Transform.h"

//GameObject
#include "../D2DEngine/Camera.h"
#include "Player.h"
#include "BulletSpawner.h"
#include "Bullet.h"
#include "Boss.h"

#include "../D2DEngine/EventManager.h"

#include "../D2DEngine/AnimationComponent.h"
#include "../D2DEngine/ColliderComponent.h"
#include "../D2DEngine/BitmapComponent.h"
#include "../D2DEngine/TextComponent.h"

#ifndef NDEBUG
#include "../D2DEngine/DebugConsole.h"
#endif // !NDEBUG


Stage1::Stage1(std::shared_ptr<D2DRenderer>winAppRenderer)
	:IScene(winAppRenderer)
{
}

Stage1::~Stage1()
{
	for (auto& iter : m_gameObject)
	{
		if (iter != nullptr)
			delete iter;
	}

	for (auto& iter : endTiles)
	{
		if (iter != nullptr)
			delete iter;
	}
}

void Stage1::Update(float dt)
{
	camera->Update(dt);
	for (auto obj : m_gameObject)
	{
		obj->Update(dt);
	}
	
	

	if (bossDead)
	{
		EndtileOn(dt);
		for (auto& iter : endTiles)
		{
			iter->Update(dt);
		}
	}

}

void Stage1::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	//그리는 순서 중요
#ifdef RELEASE
	for (auto obj : m_gameObject)
	{
		obj->Render(pRenderTarget);
	}

	for (auto iter : bulletSpawner->bullets)
	{
		iter->Render(pRenderTarget);
	}
	//보스 체력 바
	if (boss != nullptr)
	{
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		pRenderer->FillRectangle(pRenderTarget, boss->GetHpBar(), D2D1::ColorF(D2D1::ColorF::White));
	}
#endif // !RELEASE


#ifndef NDEBUG

	Stage1Comps.backGround->Render(pRenderTarget);

	player->Render(pRenderTarget);
	pRenderer->DrawRectangle(pRenderTarget, player->GetCollider()->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Purple), 2.f);

	if (boss != nullptr)
	{
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		pRenderer->FillRectangle(pRenderTarget, boss->GetHpBar(), D2D1::ColorF(D2D1::ColorF::White));
		boss->Render(pRenderTarget);
		pRenderer->DrawRectangle(pRenderTarget, boss->GetCollider()->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Purple), 2.f);
	}
	for (auto iter : bulletSpawner->bullets)
	{
		iter->Render(pRenderTarget);
		pRenderer->DrawRectangle(pRenderTarget, iter->GetCollider()->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Red), 2.f);
	}

	ground->Render(pRenderTarget);
	pRenderTarget->SetTransform(ground->transform->m_worldTransform);
	pRenderer->DrawRectangle(pRenderTarget, groundCol->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Blue), 2.f);
	tile1->Render(pRenderTarget);
	pRenderer->DrawRectangle(pRenderTarget, tileCol1->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Blue), 2.f);
	tile2->Render(pRenderTarget);
	pRenderer->DrawRectangle(pRenderTarget, tileCol2->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Blue), 2.f);
	tile3->Render(pRenderTarget);
	pRenderer->DrawRectangle(pRenderTarget, tileCol3->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Blue), 2.f);
	tile4->Render(pRenderTarget);
	pRenderer->DrawRectangle(pRenderTarget, tileCol4->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Blue), 2.f);
	
	for (auto& iter : endTiles)
	{
		iter->Render(pRenderTarget);
		pRenderer->DrawRectangle(pRenderTarget, endTileCollider->GetColliderRect(), D2D1::ColorF(D2D1::ColorF::Magenta), 1.f);
	}
	
#endif // !NDEBUG
}

void Stage1::InitScene()
{
	InitialGameObject();
	InitialEvent();
}

void Stage1::InitialGameObject()
{
	//camera
	camera = std::make_shared<Camera>(pRenderer->GetClientSize());
	camera->transform->SetLocation(0, 0);
	camera->transform->SetCenter(
		pRenderer->GetClientSize().width / 2,
		pRenderer->GetClientSize().height / 2
	);
	//BG
	Stage1Comps.backGround = new GameObject();
	Stage1Comps.bgImage = new BitmapComponent(Stage1Comps.backGround);
	Stage1Comps.backGround->transform->SetScale(1.0f, 1.0f);
	Stage1Comps.backGround->transform->SetLocation(
		(float)pRenderer->GetClientSize().width / 2,
		(float)pRenderer->GetClientSize().height / 2
	);
	Stage1Comps.bgImage->SetImage(L"../Resource/Stage1/BG1.png");

	//나중에 지우삼
	Stage1Comps.explainText = new TextComponent(Stage1Comps.backGround);
	Stage1Comps.explainText->SetTextFormat(L"궁서체", 50);
	Stage1Comps.explainText->SetText(
		L"점프 : Z\n공격 : X",
		500, 10, 1000, 500, D2D1::ColorF(D2D1::ColorF::LightCoral)
	);
	m_gameObject.push_back(Stage1Comps.backGround);

	//Player
	player = new Player(camera);
	player->transform->SetScale(0.8f, 0.8f);
	player->transform->SetLocation(
		200.f, 100//800.f
	);
	m_gameObject.push_back(player);

	//boss
	boss = new Boss(camera);
	boss->transform->SetScale(1.f, 0.9f);
	boss->transform->SetLocation(
		1200, 200
	);
	m_gameObject.push_back(boss);

	//BulletSpawner ->player
	bulletSpawner = new BulletSpawner(player);

	//ground
	ground = new GameObject();
	ground->transform->SetScale(1.0f, 1.0f);
	ground->transform->SetLocation(
		95.f, 959.f
	);
	groundrend = new BitmapComponent(ground);
	/*groundrend->m_center.x = ground->transform->GetLocation().x;
	groundrend->m_center.y = ground->transform->GetLocation().y;*/
	groundrend->SetImage(L"../Resource/Stage1/Ground.png");
	groundCol = new ColliderComponent(ground);
	D2D_RECT_F newRect = {
			groundrend->m_center.x - groundrend->m_center.x * 0.9f,
		groundrend->m_center.y - groundrend->m_center.y * 0.95f,
		groundrend->m_center.x + groundrend->m_center.x * 1.f,
		groundrend->m_center.y + groundrend->m_center.y * 0.95f
	};
	groundCol->SetColliderRect(newRect);
	m_gameObject.push_back(ground);

	//tile
	tile1 = new GameObject();
	tile1->transform->SetScale(0.9f, 0.9f);
	tile1->transform->SetLocation(100, 750);
	tileRend1 = new BitmapComponent(tile1);
	tileRend1->SetImage(L"../Resource/Stage1/Tile.png");
	tileCol1 = new ColliderComponent(tile1);
	newRect = {
		tileRend1->m_center.x - tileRend1->m_center.x * 0.9f,
		tileRend1->m_center.y - tileRend1->m_center.y * 0.9f,
		tileRend1->m_center.x + tileRend1->m_center.x * 0.9f,
		tileRend1->m_center.y + tileRend1->m_center.y * 0.9f
	};
	tileCol1->SetColliderRect(newRect);
	m_gameObject.push_back(tile1);

	tile2 = new GameObject();
	tile2->transform->SetScale(0.9f, 0.9f);
	tile2->transform->SetLocation(100, 550);
	tileRend2 = new BitmapComponent(tile2);
	tileRend2->SetImage(L"../Resource/Stage1/Tile.png");
	tileCol2 = new ColliderComponent(tile2);
	newRect = {
		tileRend2->m_center.x - tileRend2->m_center.x * 0.9f,
		tileRend2->m_center.y - tileRend2->m_center.y * 0.9f,
		tileRend2->m_center.x + tileRend2->m_center.x * 0.9f,
		tileRend2->m_center.y + tileRend2->m_center.y * 0.9f
	};
	tileCol2->SetColliderRect(newRect);
	m_gameObject.push_back(tile2);

	tile3 = new GameObject();
	tile3->transform->SetScale(0.9f, 0.9f);
	tile3->transform->SetLocation(100, 350);
	tileRend3 = new BitmapComponent(tile3);
	tileRend3->SetImage(L"../Resource/Stage1/Tile.png");
	tileCol3 = new ColliderComponent(tile3);
	newRect = {
		tileRend3->m_center.x - tileRend3->m_center.x * 0.9f,
		tileRend3->m_center.y - tileRend3->m_center.y * 0.9f,
		tileRend3->m_center.x + tileRend3->m_center.x * 0.9f,
		tileRend3->m_center.y + tileRend3->m_center.y * 0.9f
	};
	tileCol3->SetColliderRect(newRect);
	m_gameObject.push_back(tile3);

	tile4 = new GameObject();
	tile4->transform->SetScale(0.9f, 0.9f);
	tile4->transform->SetLocation(100, 150);
	tileRend4 = new BitmapComponent(tile4);
	tileRend4->SetImage(L"../Resource/Stage1/Tile.png");
	tileCol4 = new ColliderComponent(tile4);
	newRect = {
		tileRend4->m_center.x - tileRend4->m_center.x * 0.9f,
		tileRend4->m_center.y - tileRend4->m_center.y * 0.9f,
		tileRend4->m_center.x + tileRend4->m_center.x * 0.9f,
		tileRend4->m_center.y + tileRend4->m_center.y * 0.9f
	};
	tileCol4->SetColliderRect(newRect);
	m_gameObject.push_back(tile4);

	tiles.push_back(tile1);
	tiles.push_back(tile2);
	tiles.push_back(tile3);
	tiles.push_back(tile4);

	player->GetCollider()->AddCheckColliderList(groundCol->GetCollider(), "Ground");
	player->GetCollider()->AddCheckColliderList(tileCol1->GetCollider(), "Ground");
	player->GetCollider()->AddCheckColliderList(tileCol2->GetCollider(), "Ground");
	player->GetCollider()->AddCheckColliderList(tileCol3->GetCollider(), "Ground");
	player->GetCollider()->AddCheckColliderList(tileCol4->GetCollider(), "Ground");

	bulletSpawner->SetBulletColiiderInteration(tileCol1);
	bulletSpawner->SetBulletColiiderInteration(tileCol2);
	bulletSpawner->SetBulletColiiderInteration(tileCol3);
	bulletSpawner->SetBulletColiiderInteration(tileCol4);
	bulletSpawner->bossCol = boss->GetCollider();

	//camera->m_cameraCollider->AddCheckColliderList()
}

void Stage1::InitialEvent()
{
	EventManager::GetInstance().RegisterEvent(L"BossDeadEnd");
	EventManager::GetInstance().Subscribe<>(L"BossDeadEnd", std::function<void()>([this]() {
		delete boss;
		//벡터의 특정요소 지우기
		m_gameObject.erase(std::remove(m_gameObject.begin(), m_gameObject.end(), boss), m_gameObject.end());
		boss = nullptr;
		bossDead = true;
		}
	)
	);
}

void Stage1::EndScene()
{

}

//끝나고 나오는 타일 만들기.
void Stage1::EndtileOn(float dt)
{
	endTileTime += dt;
	if (endTileTime >= endTileDelay&&endTiles.size()<maxEndTileCount)
	{
		endTile = new GameObject();
		endTileBitmap = new BitmapComponent(endTile);
		endTileBitmap->SetImage(L"../Resource/Stage1/EndTile.png");
		endTileCollider = new ColliderComponent(endTile);
		endTileCollider->SetColliderRect(D2D1_RECT_F{10,5,60,20 });
		player->GetCollider()->AddCheckColliderList(endTileCollider->GetCollider(), "Ground");
		endTile->transform->SetLocation(endTileStartPosX+(50*endTiles.size()), endTilePosY);

		endTiles.push_back(endTile);
		
		endTileTime = 0.f;
	}
}


