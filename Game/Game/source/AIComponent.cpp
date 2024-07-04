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
	//���݂̏�ԂȂ�΍X�V����
	if (mState) { mState->Update();}
}

void AIComponent::ChangeState(const std::string& name)
{
	//���݂̏�Ԃ���o��
	if (mState) { mState->OnExit(); }
	//�V������Ԃ�z�񂩂�T��
	auto itr = mStateMap.find(name);
	//��Ԃ��z������猩������
	if (itr != mStateMap.end())
	{
		//��Ԃ𖼑O�ɕR�t����ꂽ�ʂ̏�Ԃ�
		mState = itr->second;
		//�V������Ԃɓ���
		mState->OnEnter();
	}
	//������Ȃ�����
	else { mState = nullptr; }
}

void AIComponent::RegisterState(AIState* state)
{
	//���O�ƕR�t���Ĕz����ɓ����
	mStateMap.emplace(state->GetName(), state);
}
