#pragma once
#include "MoveComponent.h"
class InputComponent : public MoveComponent
{
public:
	InputComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~InputComponent();
	void Update()override;
protected:
	class GameXPad* mPad;
};

