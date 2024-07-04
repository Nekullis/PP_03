#include "Enemy.h"
#include "ObjectManager.h"

Enemy::Enemy(ModeBase* game) : Character(game)
{
	mIsTargetting = true;
	RegisterAnimation();
}

Enemy::~Enemy()
{
}

void Enemy::Process()
{
	Character::Process();
}

void Enemy::Render()
{
	Character::Render();
}

void Enemy::Damage(Vector3D pos)
{
	mHp--;
}

void Enemy::RegisterAnimation()
{
	Character::RegisterAnimation();
}
