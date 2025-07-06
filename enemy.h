///*====================================================
//
//
// µ–»À!  
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

void Enemy_Create(const DirectX::XMFLOAT2& position);

#endif //Enemy_H