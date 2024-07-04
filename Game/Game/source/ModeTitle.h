#pragma once
#include "AppFrame.h"
//ƒ^ƒCƒgƒ‹
class ModeTitle : public ModeBase
{
	using base = ModeBase;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
protected:
	int mHandle;
	class GameXPad* mPad;
};

