///*====================================================
//
//
// 敌人!  
//
//
//
//=============================================================*/


#ifndef Enemy_H
#define Enemy_H
#include <DirectXMath.h>
#include "collision.h"

static constexpr unsigned int ENEMY_MAX = 256;     //敌人最大数量

void Enemy_Initialize();
void Enemy_Finalize();

void Enemy_Update(double elapsed_time);
void Enemy_Draw();


//枚举敌人类型
enum EnemyTypeID : int
{
    ENEMY_TYPE_2SHOT,
    ENEMY_TYPE_NORMAL,
};

void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position);


bool Enemy_IsEnable(int index);
Circle Enemy_GetCollision(int index);

void Enemy_Destroy(int index);
void Enemy_Damege(int index);
#endif //Enemy_H