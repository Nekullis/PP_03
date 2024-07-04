#pragma once
#include "AIState.h"
class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner);
	virtual ~AIDeath();
	//�X�V
	void Update()override;
	//�J�ڂɓ���ۂ̏���
	void OnEnter()override;
	//�J�ڂ���o��ۂ̏���
	void OnExit()override;
	//���O�擾
	const char* GetName() const override { return "death"; }
};

