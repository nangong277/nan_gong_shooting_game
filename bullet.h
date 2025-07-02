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


void Bullet_Initialize();
void Bullet_Finalize();
void Bullet_Update(double elapsed_time);
void Bullet_Draw();
void Bullet_Create(const DirectX::XMFLOAT2& position);

#endif //BULLET_H