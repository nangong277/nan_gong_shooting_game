///*====================================================
//
//
// 敌人!  
//
//
//*====================================================

#include "enemy.h"
#include <DirectXMath.h>  //为了使用 XMFLOAT2, XMVECTOR
using namespace DirectX;
#include "texture.h"       //图片加载
#include "sprite.h"     //精灵绘制


struct Enemy
{
	XMFLOAT2 position;      //	敌人的当前位置
	XMFLOAT2 velocity;      //	敌人的速度（单位是像素/秒）
	bool isEnable;          // 敌人是否激活中（true = 在场，false = 空闲）

};

static constexpr unsigned int ENEMY_MAX = 256;     //敌人最大数量
static Enemy g_Enemys[ENEMY_MAX]{};                //	所有敌人数组（最多 256 个）
static int g_EnemyTexId = -1;                      //  加载贴图后的 ID，用来绘制敌人用
static constexpr float ENEMY_WIDTH = 64.0f;        //敌人的宽度（用于判定“是否出屏幕”）






//所有敌人标记为“未启用”
//加载敌人贴图 "Boss.png" 并存入 g_EnemyTexId

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
		e.velocity = { -160.0f,0.0f };     //→ 设置敌人的速度为向左。
		break;
	}


}
