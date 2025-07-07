///*====================================================
//
//
// µÐÈËÉú³ÉÆ÷
//
//
//
//=============================================================*/


#include "enemy_spawner.h"
#include <DirectXMath.h>
using namespace DirectX;

struct EnemySpawn
{
    XMFLOAT2 position;
    EnemyTypeID id;
    int count;
    double time;
    double rate;
    double spawnTime;
    int spawnCount;
    bool isEnded;
};


static constexpr unsigned int ENEMY_SPAWNER_MAX = 100;
static EnemySpawn g_EnemySpawners[ENEMY_SPAWNER_MAX]{};
static int g_SpawnerCount = 0;
static double g_Time = 0.0;

void EnemySpawner_Initialize()
{
    g_SpawnerCount = 0;
    g_Time = 0.0;
}





void EnemySpawner_Finalize()
{

}

void EnemySpawner_Update(double elapsed_time)
{
    g_Time += elapsed_time;
    for (int i = 0; i < g_SpawnerCount; i++)
    {

        if (g_EnemySpawners[i].isEnded) continue;

        if (g_EnemySpawners[i].time > g_Time) break;

        if (g_EnemySpawners[i].spawnCount == 0)
        {
            g_EnemySpawners[i].spawnTime = g_Time - g_EnemySpawners[i].rate - 0.00001;
        }

        if (g_Time - g_EnemySpawners[i].spawnTime >= g_EnemySpawners[i].rate)
        {
            Enemy_Create(g_EnemySpawners[i].id, g_EnemySpawners[i].position);
            g_EnemySpawners[i].spawnCount++;
            if (g_EnemySpawners[i].spawnCount >= g_EnemySpawners[i].count)
            {
                g_EnemySpawners[i].isEnded = true;
            }
            g_EnemySpawners[i].spawnTime = g_Time;
        }
    }

}

void EnemySpawner_Create(const XMFLOAT2& position, EnemyTypeID id, double spawn_time, double spawn_rate, int spawn_count)
{

    if (g_SpawnerCount >= ENEMY_SPAWNER_MAX) return;

    EnemySpawn* pEs = &g_EnemySpawners[g_SpawnerCount];
    pEs->position = position;
    pEs->id = id;
    pEs->time = spawn_time;
    pEs->rate = spawn_rate;
    pEs->count = spawn_count;
    pEs->isEnded = false;
    pEs->spawnCount = 0;
    pEs->spawnTime = 0.0;
    g_SpawnerCount++;
}
