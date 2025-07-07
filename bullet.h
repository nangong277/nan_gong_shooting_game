///*====================================================
//
//
// ×Óµ¯!  
//
//
//
//=============================================================*/


#ifndef BULLET_H
#define BULLET_H
#include <DirectXMath.h>
#include "collision.h"
static constexpr unsigned int BULLET_MAX = 1024;

void Bullet_Initialize();
void Bullet_Finalize();
void Bullet_Update(double elapsed_time);
void Bullet_Draw();
void Bullet_Create(const DirectX::XMFLOAT2& position);

bool Bullet__IsEnable(int index);
Circle Bullet__GetCollision(int index);

#endif //BULLET_H