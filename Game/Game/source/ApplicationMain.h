#pragma once
#include "AppFrame.h"
//#include <thread>
//アプリケーションのメイン部分。ここからモード変移などを行うクラス
class ApplicationMain : public ApplicationBase
{
	using base = ApplicationBase;
public:
	bool Initialize(HINSTANCE instance)override;
	bool Terminate()override;
	bool Input();
	bool Process();
	bool Render();
protected:
	//初期化
	std::thread* _init;
};

