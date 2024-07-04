#pragma once
#include "AppFrame.h"
#include <unordered_map>
class AIComponent : public Component
{
public:
	AIComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~AIComponent();
	//更新
	void Update() override;
	//状態変更
	void ChangeState(const std::string& name);
	//状態の登録
	void RegisterState(class AIState* state);
private:
	//インスタンスの紐付け
	std::unordered_map <std::string, class AIState*> mStateMap;
	//現在の状態
	class AIState* mState;
};

