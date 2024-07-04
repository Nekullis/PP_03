#pragma once
#include "AppFrame.h"
class DrawBillboardComponent : public Component
{
public:
	DrawBillboardComponent(class ObjectBase* owner, int updateowder = 150);
	virtual ~DrawBillboardComponent();
	void Update()override;
	//セッター
	void SetHandle(int handle) { mHandle = handle; }
protected:
	int mHandle;
};

