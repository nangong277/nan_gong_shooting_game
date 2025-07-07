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




#endif //Enemy_H