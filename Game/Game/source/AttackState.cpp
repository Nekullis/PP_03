#include "AttackState.h"
AttackState::AttackState()
{
	ATTACK attack = { Player::ANIMATION::NONE,0,0,0,0,0,0,0,false};
	mAttack = attack;
}

AttackState::~AttackState()
{
}

void AttackState::Update()
{
}
