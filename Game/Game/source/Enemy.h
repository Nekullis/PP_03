#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy(ModeBase* game);
	virtual ~Enemy();
	virtual void RegisterAnimation()override;
	virtual void Process()override;
	virtual void Render()override;
	virtual void Damage(Vector3D pos);
protected:
};

