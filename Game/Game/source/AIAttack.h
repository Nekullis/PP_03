#pragma once
#include "AIState.h"
class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner);
	virtual ~AIAttack();
	//更新
	void Update();
	//遷移に入る際の処理
	void OnEnter();
	//遷移から出る際の処理
	void OnExit();
	//名前取得
	const char* GetName()const override { return "attack"; }
};

