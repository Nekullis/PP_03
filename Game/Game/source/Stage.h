#pragma once
#include "AppFrame.h"
class Stage : public ObjectBase
{
public:
	static Stage* stageInstance;
	Stage(ModeBase* game);
	virtual ~Stage();
	void Process()override;
	void Render()override;
	//ÉQÉbÉ^Å[
	static Stage* GetInstance() { return stageInstance; }
protected:
	int mHandle;
	class ObjectManager* mManager;
};

