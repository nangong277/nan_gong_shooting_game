/*====================================================


ゲーム本体「game.h」



=============================================================*/


#include "game.h"
#include "player.h"
#include <DirectXMath.h>
#include "bullet.h"
#include "enemy.h"

using namespace DirectX;


static double g_Time = 0.0f;
static double g_CreateTime = 0.0f;


void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450.0f - 32.0f});
	Bullet_Initialize();
	Enemy_Initialize();

}

void Game_Finalize()
{
	Bullet_Finalize();
	Player_Finalize();
	Enemy_Finalize();

}

void Game_Update(double elapsed_time)
{
	if (g_Time - g_CreateTime > 2.0f)
	{
		Enemy_Create({1600.0f,450 - 32.0f });
		g_CreateTime = g_Time;

	}
	g_Time += elapsed_time;
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
