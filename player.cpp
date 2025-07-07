#include "player.h"
#include <DirectXMath.h>
#include "sprite.h"       //showing function
#include "texture.h"       //showing function
#include "keylogger.h"
#include "bullet.h"
using namespace DirectX;

static constexpr float PLAYER_WIDTH = 64.0f;
static constexpr float PLAYER_HEIGHT = 64.0f;

static DirectX::XMFLOAT2 g_PlayerPosition{};
static DirectX::XMFLOAT2 g_PlayerVelocity{};
static int g_PlayerTexId = -1;
static constexpr Circle g_PlayerCollision{ { 32.0f, 32.0f }, 32.0f };
static bool g_PlayerEnable = true;


//static XMVECTOR 计算用向量(供Intel 的cpu中的特殊浮点运算单元使用，条件苛刻)

void Player_Initialize(const XMFLOAT2& position)
{
	g_PlayerPosition = position;
	g_PlayerVelocity = { 0.0f , 0.0f };
	g_playerEnable = ture;
	g_PlayerTexId = Texture_Load(L"resource/texture/kokosozai.png");
}

void Player_Finalize()
{
}

void Player_Update(double elapsed_time)
{
	//演算型との転換
	if (!g_PlayerEnable) return;
	XMVECTOR position = XMLoadFloat2(&g_PlayerPosition);
	XMVECTOR velocity = XMLoadFloat2(&g_PlayerVelocity);

	XMVECTOR direction{};

	if (KeyLogger_IsPressed(KK_W))
	{
		direction += { 0.0f, -1.0f };
	}
	if (KeyLogger_IsPressed(KK_S))
	{
		direction += { 0.0f, +1.0f };
	}
	if (KeyLogger_IsPressed(KK_A))
	{
		direction += { -1.0f, 0.0f };
	}
	if (KeyLogger_IsPressed(KK_D))
	{
		direction += { 1.0f, 0.0f };
	}

	direction = XMVector2Normalize(direction); //单位化 长度为1 ， 1的单位向量

	velocity += direction * 100.0f * elapsed_time;

	position += velocity;

	velocity *= 0.9;

	XMStoreFloat2(&g_PlayerPosition, position);
	XMStoreFloat2(&g_PlayerVelocity, velocity);

	if(KeyLogger_IsTrigger(KK_SPACE)){
		Bullet_Create({ g_PlayerPosition.x,g_PlayerPosition.y });
	}


}

void Player_Draw()
{
	if (!g_PlayerEnable) return;
	Sprite_Draw(g_PlayerTexId,
		g_PlayerPosition.x,
		g_PlayerPosition.y,
		64.0f, 64.0f,
		0, 0,
		32, 32);
}
bool Player_IsEnable()
{
	return g_PlayerEnable;
}

Circle Player_GetCollision()
{
	float cx = g_PlayerPosition.x + g_PlayerCollision.center.x;
	float cy = g_PlayerPosition.y + g_PlayerCollision.center.y;

	return { { cx, cy }, g_PlayerCollision.radius };
}

void Player_Destroy()
{
	g_PlayerEnable = false;
}
//上面的数值最好定义为constexpr定值}
