#pragma once
#include "AIState.h"
class AIVigilance :public AIState
{
public:
	AIVigilance(class AIComponent* owner);
	virtual ~AIVigilance();
	//更新
	void Update()override;
	//遷移に入る際の処理
	void OnEnter()override;
	//遷移から出る際の処理
	void OnExit()override;
	//名前取得
	const char* GetName()const override{ return "vigilance"; }
};

