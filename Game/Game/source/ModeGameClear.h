#pragma once
#include "AppFrame.h"
class ModeGameClear : public ModeBase
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
