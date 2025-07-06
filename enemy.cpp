///*====================================================
//
//
// ����!  
//
//
//*====================================================

#include "enemy.h"
#include <DirectXMath.h>  //Ϊ��ʹ�� XMFLOAT2, XMVECTOR
using namespace DirectX;
#include "texture.h"       //ͼƬ����
#include "sprite.h"     //�������


struct Enemy
{
	XMFLOAT2 position;      //	���˵ĵ�ǰλ��
	XMFLOAT2 velocity;      //	���˵��ٶȣ���λ������/�룩
	bool isEnable;          // �����Ƿ񼤻��У�true = �ڳ���false = ���У�

};

static constexpr unsigned int ENEMY_MAX = 256;     //�����������
static Enemy g_Enemys[ENEMY_MAX]{};                //	���е������飨��� 256 ����
static int g_EnemyTexId = -1;                      //  ������ͼ��� ID���������Ƶ�����
static constexpr float ENEMY_WIDTH = 64.0f;        //���˵Ŀ�ȣ������ж����Ƿ����Ļ����






//���е��˱��Ϊ��δ���á�
//���ص�����ͼ "Boss.png" ������ g_EnemyTexId

void Enemy_Initialize()
{
	for (Enemy& e : g_Enemys)
	{
		e.isEnable = false;
	}
	g_EnemyTexId = Texture_Load(L"resource/texture/Boss.png");
}

void Enemy_Finalize()
{
}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemys)
	{
		if (!e.isEnable) continue;

		XMVECTOR position = XMLoadFloat2(&e.position);
		XMVECTOR velocity = XMLoadFloat2(&e.velocity);

		position += velocity * elapsed_time;

		XMStoreFloat2(&e.position, position);
		XMStoreFloat2(&e.velocity, velocity);

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
		if (!e.isEnable)continue;

		Sprite_Draw(g_EnemyTexId,
			e.position.x, e.position.y,
			132.0f, 132.0f,     // ��ʾΪ 32x32 ��С
			10, 256,         // �ü�������㣨����ƫ�ƣ�
			1024, 1024);        // �ü���С����ͼ��Ҫȡ���

	}
}

void Enemy_Create(const DirectX::XMFLOAT2& position)
{

	for (Enemy& e : g_Enemys)
	{
		if (e.isEnable)continue;
		//���ֿյ�

		e.isEnable = true;
		e.position = position;
		e.velocity = { -160.0f,0.0f };     //�� ���õ��˵��ٶ�Ϊ����
		break;
	}


}
