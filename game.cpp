/*====================================================


ゲーム本体「game.h」



=============================================================*/


#include "game.h"
#include "player.h"
#include <DirectXMath.h>
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"

using namespace DirectX;


static double g_Time = 0.0f;
static double g_CreateTime = 0.0f;


void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f });
	Bullet_Initialize();
	Enemy_Initialize();
	EnemySpawner_Initialize();

	EnemySpawner_Create({ 1600, 128 }, ENEMY_TYPE_NORMAL, 3.0, 0.3, 5);
	EnemySpawner_Create({ 1600, 900 - 128 - 64 }, ENEMY_TYPE_NORMAL, 5.0, 0.3, 5);
	EnemySpawner_Create({ 1600, 450 - 64 }, ENEMY_TYPE_2SHOT, 5.0, 0.1, 5);
	EnemySpawner_Create({ 1600, 450 - 64 }, ENEMY_TYPE_2SHOT, 8.0, 0.5, 3);
}

void Game_Finalize()
{
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

}

void Game_Draw()
{
	Enemy_Draw();
	Bullet_Draw();
	Player_Draw();
}
