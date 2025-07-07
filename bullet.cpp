#include "bullet.h"
#include <DirectXMath.h>
#include "direct3d.h"
#include "texture.h"
#include "sprite.h" 
#include "collision.h" 
#include "effect.h"
using namespace DirectX;


struct Bullet
{
	XMFLOAT2 position;
	XMFLOAT2 velocity;
	double lifeTime;
	bool isEnable;
	Circle collision;
};



static Bullet g_Bullets[BULLET_MAX]{};
static int g_BulletTexId = -1;


void Bullet_Initialize()
{
	for (Bullet& b : g_Bullets)
	{

	}
	g_BulletTexId = Texture_Load(L"resource/texture/boom1.png");

}

void Bullet_Finalize()
{
}

void Bullet_Update(double elapsed_time)
{
	for (Bullet& b : g_Bullets)
	{
		if (!b.isEnable) continue;



		XMVECTOR position = XMLoadFloat2(&b.position);
		XMVECTOR velocity = XMLoadFloat2(&b.velocity);

		position += velocity * elapsed_time;


		XMStoreFloat2(&b.position, position);
		XMStoreFloat2(&b.velocity, velocity);


		b.lifeTime += elapsed_time;
		if (b.lifeTime >= 5.0f)
		{
			b.isEnable = false;
		}

		if (b.position.x > Direct3D_GetBackBufferWidth())
		{
			b.isEnable = false;
		}
		//b.position += b.velocity;
	}
}

void Bullet_Draw()
{
	for (Bullet& b : g_Bullets)
	{
		if (!b.isEnable)continue;
		Sprite_Draw(g_BulletTexId,
			b.position.x, b.position.y,
			32.0f, 32.0f,     // 显示为 32x32 大小
			10, 256,         // 裁剪区域起点（中心偏移）
			1024, 1024);        // 裁剪大小（新图中要取多大）

	}
}


void Bullet_Create(const XMFLOAT2& position)
{
	for (Bullet& b : g_Bullets)
	{

		if (b.isEnable) continue;

		// 空き領域発見
		b.isEnable = true;
		b.lifeTime = 0.0f;
		b.position = position;
		b.velocity = { 400.0f, 0.0f };
		b.collision = { { 16.0f, 16.0f }, 16.0f };
		break;
	}
}

bool Bullet_IsEnable(int index)
{
	return g_Bullets[index].isEnable;
}

void Bullet_Destroy(int index)
{
	g_Bullets[index].isEnable = false;
}

Circle Bullet_GetCollision(int index)
{
	float cx = g_Bullets[index].collision.center.x
		+ g_Bullets[index].position.x;
	float cy = g_Bullets[index].collision.center.y
		+ g_Bullets[index].position.y;

	return { { cx, cy }, g_Bullets[index].collision.radius };
}
