#include "AIComponent.h"
#include "AIState.h"
AIComponent::AIComponent(ObjectBase* owner, int updateowder) :Component(owner, updateowder)
{
	mOwner->AddComponent(this);
}

AIComponent::~AIComponent()
{
}

void AIComponent::Update()
{
	//現在の状態ならば更新する
	if (mState) { mState->Update();}
}

void AIComponent::ChangeState(const std::string& name)
{
	//現在の状態から出る
	if (mState) { mState->OnExit(); }
	//新しい状態を配列から探す
	auto itr = mStateMap.find(name);
	//状態が配列内から見つかった
	if (itr != mStateMap.end())
	{
		//状態を名前に紐付けられた別の状態に
		mState = itr->second;
		//新しい状態に入る
		mState->OnEnter();
	}
	//見つからなかった
	else { mState = nullptr; }
}

void AIComponent::RegisterState(AIState* state)
{
	//名前と紐付けて配列内に入れる
	mStateMap.emplace(state->GetName(), state);
}
