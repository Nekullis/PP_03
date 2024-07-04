#pragma once
#include "AIState.h"
class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner);
	virtual ~AIDeath();
	//更新
	void Update()override;
	//遷移に入る際の処理
	void OnEnter()override;
	//遷移から出る際の処理
	void OnExit()override;
	//名前取得
	const char* GetName() const override { return "death"; }
};

