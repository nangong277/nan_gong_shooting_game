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

struct EnemyType
{
	int texId;
	int tx, ty, tw, th;
};

struct Enemy
{
	int typeId;
	XMFLOAT2 position;      //	���˵ĵ�ǰλ��
	XMFLOAT2 velocity;      //	���˵��ٶȣ���λ������/�룩
	float offsetY;
	double lifeTime;
	bool isEnable;          // �����Ƿ񼤻��У�true = �ڳ���false = ���У�

};

static constexpr unsigned int ENEMY_MAX = 256;     //�����������
static Enemy g_Enemys[ENEMY_MAX]{};                //	���е������飨��� 256 ����
static int g_EnemyTexId = -1;                      //  ������ͼ��� ID���������Ƶ�����
static constexpr float ENEMY_WIDTH = 64.0f;        //���˵Ŀ�ȣ������ж����Ƿ����Ļ����


//���˲���λ��
static EnemyType g_EnemyTypes[] = {
	{ -1, 32 * 5, 32 * 36, 32, 32 }, // �� �� 5 �У��� 36 ��
	{ -1, 32 * 8 ,32 * 36, 32, 32 }  // �� �� 8 �У��� 36 ��
};




//���е��˱��Ϊ��δ���á�
//���ص�����ͼ "Boss.png" ������ g_EnemyTexId

void Enemy_Initialize()
{
	for (Enemy& e : g_Enemys)
	{
		e.isEnable = false;
	}

	g_EnemyTypes[0].texId = Texture_Load(L"resource/texture/Boss.png");
	g_EnemyTypes[1].texId = Texture_Load(L"resource/texture/Boss.png");
}


void Enemy_Finalize()
{
}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemys)
	{
		if (!e.isEnable) continue;



		switch (e.typeId)
		{
		case ENEMY_TYPE_NORMAL:
			XMVECTOR position = XMLoadFloat2(&e.position);
			XMVECTOR velocity = XMLoadFloat2(&e.velocity);

			position += velocity * elapsed_time;

			XMStoreFloat2(&e.position, position);
			XMStoreFloat2(&e.velocity, velocity);

			break;
		case ENEMY_TYPE_2SHOT:
			e.position.x += e.velocity.x * elapsed_time;
			e.position.y = e.offsetY + sin(e.lifeTime * 3.0) * 120.f;
			break;
		}

		e.lifeTime += elapsed_time;

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
		if (!e.isEnable) continue;

		Sprite_Draw(
			g_EnemyTypes[e.typeId].texId,
			e.position.x, e.position.y,
			ENEMY_WIDTH, 64.0f,
			g_EnemyTypes[e.typeId].tx,
			g_EnemyTypes[e.typeId].ty,
			g_EnemyTypes[e.typeId].tw,
			g_EnemyTypes[e.typeId].th);
	}
}

void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position)
{

	for (Enemy& e : g_Enemys)
	{
		if (e.isEnable)continue;
		//���ֿյ�
		e.isEnable = true;
		e.typeId = id;
		e.offsetY = position.y;
		e.position = position;
		e.velocity = { -160.0f,0.0f };     //�� ���õ��˵��ٶ�Ϊ����
		e.lifeTime = 0.0;
		break;
	}

}
