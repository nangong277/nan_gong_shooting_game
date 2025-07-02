#include <Windows.h>
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include "game_window.h"
#include "direct3d.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"
#include "Sprite_Anim.h"
#include "debug_text.h"
#include <sstream>
#include "system_timer.h" //direct 3d toolkit
#include <DirectXmath.h>
using namespace DirectX;
#include "keylogger.h"
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "mouse.h"
#include "game.h"


//test这是测试github是否正常呢

/*----------------------------------------------------------------------
横着是 x % 5
竖着是 x / 5

提出文件要求
。exe
。cso 两个
使用中的texture file

更改文件路径  最外部文件夹名/下一级文件夹名/“素材名.文件格式”

main function
------------------------------------------------------------------------*/


//void ProcessInput(UINT message, WPARAM wParam, float& acc, bool& isjumped);

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{ 
	(void)CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME   （禁止放大缩小窗口）
	// WS_OVERLAPPEDWINDOW &  ~WS_THICKFRAME
	//显示制作的窗口

	HWND hWnd = GameWindowCreate(hInstance);

	SystemTimer_Initialize();
	KeyLogger_Initialize();
	Mouse_Initialize(hWnd);

	Direct3D_Initialize(hWnd);

	Shader_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());

	//注意 任何初始化都要在D3D和shader初始化之后进行
	//Polygon_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());

	Texture_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());

	

	Sprite_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());

	//不能是纯黑  不能有静止的画面 

	SpriteAnim_Initialize();

	hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetContext(),
		L"resource/texture/consolab_ascii_512.png",
		Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
		0.0f, 0.0f,
		0, 0,
		0.0f, 12.0f);


	Game_Initialize();

	//Mouse_SetVisible(false);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//fps  フreーム計測用计算帧率

	double exec_last_time = SystemTimer_GetTime();
	double fps_last_time = exec_last_time;
	double current_time = 0.0;
	ULONG frame_count = 0;
	double fps = 0.0;

	
	
	//GAME LOOP  & MESSAGE LOOP
	MSG msg;
	//unreal中不能定义循环（被封存），只能制作event
	 //但是unity中可以修改循环
	do
	{ 
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))  //peekmessage使用时
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			

			//fps 計測用
			current_time = SystemTimer_GetTime(); //最新时间
			double elapsed_time = current_time - fps_last_time; //fps計測用の経つ時間を計算    
			/*，在每个循环迭代中，current_time 会随着时间的推移不断更新，而 fps_last_time 只有在进行FPS计算后才会更新。这种设计允许代码在每经过一秒时计算一次FPS，而不是在每个帧都计算。

			这样做的目的是为了计算每秒的帧数（FPS），而不是每帧的帧数。通过这种方式，程序可以在每秒结束时计算出当前的平均帧率，并在下一个秒周期开始时重置帧计数。*/

			if (elapsed_time >= 1.0)
			{
				fps = frame_count / elapsed_time;
				fps_last_time = current_time; //fpsを測定した時間を保存
				frame_count = 0;   //カウントをクリア
			}




			//1/60sごとに実行
			elapsed_time = current_time - exec_last_time;
			if (elapsed_time >= (1.0 / 60.0)) 
			{
			
				//if (true){
				exec_last_time = current_time;

				//ゲーム更新

				KeyLogger_Update();
				
				Game_Update(elapsed_time);

				SpriteAnimUpdate(elapsed_time);

				//ゲームの描画
				Direct3D_Clear();

				Sprite_Begin();

				Game_Draw();
	
				
				dt.Draw();
				dt.Clear();

				std::stringstream ss;
				ss << " fps : " << fps << std::endl;
				dt.SetText(ss.str().c_str());
				//#endif

				Direct3D_Present();


				frame_count++;
				
			}

		}
	} while (msg.message != WM_QUIT);



	Game_Finalize();
	SpriteAnim_Finalize();

	Texture_Finalize();


	//Polygon_Finalize();

	Sprite_Finalize();

	Shader_Finalize();
	Direct3D_Finalize();
	Mouse_Finalize();
	return (int)msg.wParam;

}

