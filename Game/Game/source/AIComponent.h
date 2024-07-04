#pragma once
#include "AppFrame.h"
#include <unordered_map>
class AIComponent : public Component
{
public:
	AIComponent(class ObjectBase* owner, int updateowder = 10);
	virtual ~AIComponent();
	//�X�V
	void Update() override;
	//��ԕύX
	void ChangeState(const std::string& name);
	//��Ԃ̓o�^
	void RegisterState(class AIState* state);
private:
	//�C���X�^���X�̕R�t��
	std::unordered_map <std::string, class AIState*> mStateMap;
	//���݂̏��
	class AIState* mState;
};

