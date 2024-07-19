#pragma once
#include "../D2DEngine/SceneGraph.h"


//object 전방선언
class Player;
class Boss;
class BulletSpawner;
class GameObject;
class Camera;

class EventManager;


//component 전방선언
class AnimationComponent;
class RenderComponent;
class ColliderComponent;
class BitmapComponent;
class TextComponent;

class Stage1:public IScene
{
	struct Stage1Component
	{
		GameObject* backGround;
		BitmapComponent* bgImage;
	//게임설명 text 나중에 지우자
		TextComponent* explainText;
	}Stage1Comps;

	//player
	Player* player;
	BulletSpawner* bulletSpawner;

	//Boss
	Boss* boss;

	//camera
	std::shared_ptr<Camera> camera;

	//tile
	GameObject* tile1;
	ColliderComponent* tileCol1;
	BitmapComponent* tileRend1;
	GameObject* tile2;
	ColliderComponent* tileCol2;
	BitmapComponent* tileRend2;
	GameObject* tile3;
	ColliderComponent* tileCol3;
	BitmapComponent* tileRend3;
	GameObject* tile4;
	ColliderComponent* tileCol4;
	BitmapComponent* tileRend4;
	GameObject* ground;
	ColliderComponent* groundCol;
	BitmapComponent* groundrend;
	
	std::vector<GameObject*>tiles;

	std::vector<GameObject*>endTiles;
	GameObject* endTile;
	BitmapComponent* endTileBitmap;
	ColliderComponent* endTileCollider;

	//GameObject
	std::vector<GameObject*>m_gameObject;



public:
	Stage1(std::shared_ptr<D2DRenderer>winAppRenderer);
	virtual ~Stage1();
	void Update(float dt)override;
	void Render(ID2D1HwndRenderTarget*pRenderTarget)override;
	void InitScene()override;
	void InitialGameObject()override;
	void InitialEvent();
	void EndScene()override;

	void EndtileOn(float dt);

private:
	bool bossDead = false;
	float endTileDelay = 0.12f;
	float endTileTime = 0.f;
	float endTileStartPosX=300.f;
	float endTilePosY=923.f;
	int maxEndTileCount = 25;
};

