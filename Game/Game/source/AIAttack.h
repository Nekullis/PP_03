#pragma once
#include "AIState.h"
class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner);
	virtual ~AIAttack();
	//�X�V
	void Update();
	//�J�ڂɓ���ۂ̏���
	void OnEnter();
	//�J�ڂ���o��ۂ̏���
	void OnExit();
	//���O�擾
	const char* GetName()const override { return "attack"; }
};

