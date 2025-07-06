///*====================================================
//
//
// 敌人!  
//
//
//

#include "enemy.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "texture.h"
#include "sprite.h" 


struct Enemy
{
	XMFLOAT2 position;
	XMFLOAT2 velocity;
	bool isEnable;

};

static constexpr unsigned int ENEMY_MAX = 256;
static Enemy g_Enemys[ENEMY_MAX]{};
static int g_EnemyTexId = -1;
static constexpr float ENEMY_WIDTH = 64.0f;

void Enemy_Initialize()
{
	for (Enemy& e : g_Enemys)
	{
		e.isEnable = false;
	}
	g_EnemyTexId = Texture_Load(L"resource/texture/Boss.png");
}

void Enemy_Finalize()
{
}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemys)
	{
		if (!e.isEnable) continue;

		XMVECTOR position = XMLoadFloat2(&e.position);
		XMVECTOR velocity = XMLoadFloat2(&e.velocity);

		position += velocity * elapsed_time;

		XMStoreFloat2(&e.position, position);
		XMStoreFloat2(&e.velocity, velocity);

		if (e.position.x + ENEMY_WIDTH < 0.0f)
		{
			e.isEnable = false;
		}
	}
}

void Enemy_Draw()
{
	for (Enemy& e : g_Enemys)
	{
		if (!e.isEnable)continue;

		Sprite_Draw(g_EnemyTexId,
			e.position.x, e.position.y,
			132.0f, 132.0f,     // 显示为 32x32 大小
			10, 256,         // 裁剪区域起点（中心偏移）
			1024, 1024);        // 裁剪大小（新图中要取多大）

	}
}

void Enemy_Create(const DirectX::XMFLOAT2& position)
{

	for (Enemy& e : g_Enemys)
	{
		if (e.isEnable)continue;
		//发现空地

		e.isEnable = true;
		e.position = position;
		e.velocity = { -160.0f,0.0f };
		break;
	}


}
