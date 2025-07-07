/*====================================================


ゲーム本体「game.h」



=============================================================*/


#include "game.h"
#include "player.h"
#include <DirectXMath.h>
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"
#include "effect.h"



void hitJudgmentBulletVSEnemy();
void hitJudgmentPlayerVSEnemy();

using namespace DirectX;


static double g_Time = 0.0f;
static double g_CreateTime = 0.0f;



void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f });
	Bullet_Initialize();
	Enemy_Initialize();
	EnemySpawner_Initialize();
	Effect_Initialize();

	EnemySpawner_Create({ 1600, 128 }, ENEMY_TYPE_NORMAL, 3.0, 0.3, 5);
	EnemySpawner_Create({ 1600, 900 - 128 - 64 }, ENEMY_TYPE_NORMAL, 5.0, 0.3, 5);
	EnemySpawner_Create({ 1600, 450 - 64 }, ENEMY_TYPE_2SHOT, 5.0, 0.1, 5);
	EnemySpawner_Create({ 1600, 450 - 64 }, ENEMY_TYPE_2SHOT, 8.0, 0.5, 3);
}

void Game_Finalize()
{
	Effect_Finalize();
	EnemySpawner_Finalize();
	Bullet_Finalize();
	Player_Finalize();
	Enemy_Finalize();

}

void Game_Update(double elapsed_time)
{
	EnemySpawner_Update(elapsed_time);
	Player_Update(elapsed_time);
	Bullet_Update(elapsed_time);
	Enemy_Update(elapsed_time);
	hitJudgmentBulletVSEnemy();
	hitJudgmentPlayerVSEnemy();

	Effect_Update(elapsed_time);
}

void hitJudgmentBulletVSEnemy()
{
	for (int bi = 0; bi < BULLET_MAX; bi++)
	{
		
		if (!Bullet_IsEnable(bi)) continue;

		for (int ei = 0; ei < ENEMY_MAX; ei++)
		{

			if (!Enemy_IsEnable(ei)) continue;

			if (Collision_IsOverlapCircle(
				Bullet_GetCollision(bi),
				Enemy_GetCollision(ei)))
			{
				// ヒット〜
				Bullet_Destroy(bi);
				Enemy_Damege(ei);
			}
		}
	}
}
void hitJudgmentPlayerVSEnemy()
{
    if (!Player_IsEnable()) return;

	for (int ei = 0; ei < ENEMY_MAX; ei++)
	{
        if (!Enemy_IsEnable(ei)) continue;

        if (Collision_IsOverlapCircle(
			Player_GetCollision(),
			Enemy_GetCollision(ei)))
		{
            // ヒット～
			Player_Destroy();
			Enemy_Destroy(ei);
			Effect_Create(Enemy_GetCollision(ei).center);
        }
    }
}



void Game_Draw()
{
	Enemy_Draw();
	Bullet_Draw();
	Player_Draw();
	Effect_Draw();
}
