#pragma once
#include "AIState.h"
class AIVigilance :public AIState
{
public:
	AIVigilance(class AIComponent* owner);
	virtual ~AIVigilance();
	//�X�V
	void Update()override;
	//�J�ڂɓ���ۂ̏���
	void OnEnter()override;
	//�J�ڂ���o��ۂ̏���
	void OnExit()override;
	//���O�擾
	const char* GetName()const override{ return "vigilance"; }
};

