#pragma once
#include "AppFrame.h"
class ModeGameOver :public ModeBase
{
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	int mHandle;
	class GameXPad* mPad;
};

