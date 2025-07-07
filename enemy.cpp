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

struct EnemyType
{
	int texId;
	int tx, ty, tw, th;
};

struct Enemy
{
	int typeId;
	XMFLOAT2 position;      //	敌人的当前位置
	XMFLOAT2 velocity;      //	敌人的速度（单位是像素/秒）
	float offsetY;
	double lifeTime;
	bool isEnable;          // 敌人是否激活中（true = 在场，false = 空闲）

};

static constexpr unsigned int ENEMY_MAX = 256;     //敌人最大数量
static Enemy g_Enemys[ENEMY_MAX]{};                //	所有敌人数组（最多 256 个）
static int g_EnemyTexId = -1;                      //  加载贴图后的 ID，用来绘制敌人用
static constexpr float ENEMY_WIDTH = 64.0f;        //敌人的宽度（用于判定“是否出屏幕”）


//敌人裁切位置
static EnemyType g_EnemyTypes[] = {
	{ -1, 32 * 5, 32 * 36, 32, 32 }, // ← 第 5 列，第 36 行
	{ -1, 32 * 8 ,32 * 36, 32, 32 }  // ← 第 8 列，第 36 行
};




//所有敌人标记为“未启用”
//加载敌人贴图 "Boss.png" 并存入 g_EnemyTexId

void Enemy_Initialize()
{
	for (Enemy& e : g_Enemys)
	{
		e.isEnable = false;
	}

	g_EnemyTypes[0].texId = Texture_Load(L"resource/texture/Boss.png");
	g_EnemyTypes[1].texId = Texture_Load(L"resource/texture/Boss.png");
}


void Enemy_Finalize()
{
}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemys)
	{
		if (!e.isEnable) continue;



		switch (e.typeId)
		{
		case ENEMY_TYPE_NORMAL:
			XMVECTOR position = XMLoadFloat2(&e.position);
			XMVECTOR velocity = XMLoadFloat2(&e.velocity);

			position += velocity * elapsed_time;

			XMStoreFloat2(&e.position, position);
			XMStoreFloat2(&e.velocity, velocity);

			break;
		case ENEMY_TYPE_2SHOT:
			e.position.x += e.velocity.x * elapsed_time;
			e.position.y = e.offsetY + sin(e.lifeTime * 3.0) * 120.f;
			break;
		}

		e.lifeTime += elapsed_time;

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
		if (!e.isEnable) continue;

		Sprite_Draw(
			g_EnemyTypes[e.typeId].texId,
			e.position.x, e.position.y,
			ENEMY_WIDTH, 64.0f,
			g_EnemyTypes[e.typeId].tx,
			g_EnemyTypes[e.typeId].ty,
			g_EnemyTypes[e.typeId].tw,
			g_EnemyTypes[e.typeId].th);
	}
}

void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position)
{

	for (Enemy& e : g_Enemys)
	{
		if (e.isEnable)continue;
		//发现空地
		e.isEnable = true;
		e.typeId = id;
		e.offsetY = position.y;
		e.position = position;
		e.velocity = { -160.0f,0.0f };     //→ 设置敌人的速度为向左。
		e.lifeTime = 0.0;
		break;
	}

}
