#pragma once
#include "AppFrame.h"
class PolygonEffect : public ObjectBase
{
public:
	PolygonEffect(ModeBase* game);
	virtual ~PolygonEffect();
	virtual void Process()override;
	virtual void Render()override;
};

