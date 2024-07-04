#include "CollisionManager.h"
#include "CapsuleColComponent.h"
#include "WeaponColComponent.h"
#include "AttackManager.h"
#include "DamageEffect.h"
#include "EnemyMob.h"
#include "ModeGame.h"
#include <iostream>
CollisionManager* CollisionManager::colMaInstance = nullptr;
CollisionManager::CollisionManager()
{
	colMaInstance = this;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddCollision(CollisionComponent* col)
{
	mCollisionList.emplace_back(col);
}

void CollisionManager::Delete()
{

}

void CollisionManager::Update()
{
	
	float dist_captocap = 0.0;
	float seg = 170.0;;
	//�����Ɛ����̍ŒZ���������߂�ۂɎg���ϐ��B
	Vector3D v1m;
	Vector3D v2m;
	double t1 = 0.0;
	double t2 = 0.0;
	//�e�Փ˔���R���|�[�l���g�̃v���Z�X�X�V
	for (auto&& col : mCollisionList)
	{
		col->Update();
	}
	for (auto&& col_i : mCollisionList)
	{
		for (auto&& col_j : mCollisionList)
		{
			//�����R���|�[�l���g�͏��O
			if (col_i == col_j) { continue; }
			//���v���a�����߂Ă���
			float add_rad = col_i->GetRadius() + col_j->GetRadius();
			//�����̎n�_�A�I�_������
			Vector3D pos_i_s;
			Vector3D pos_i_e;
			Vector3D pos_j_s;
			Vector3D pos_j_e;
			//�ǂ�����Փ˔���^�C�v���J�v�Z���̏ꍇ
			if (col_i->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE && col_j->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE)
			{
				//�n�_�A�I�_���e�R���|�[�l���g�Őݒ肵���n�_�A�I�_��
				pos_i_s = col_i->GetPos();
				pos_i_e = col_i->GetPos() + Vector3D(0.0, seg, 0.0);
				pos_j_s = col_j->GetPos();
				pos_j_e = col_j->GetPos() + Vector3D(0.0, seg, 0.0);
				//�����Ɛ����̍ŒZ���������߂�
				dist_captocap = MyMath::DisSegAndSeg(pos_i_s, pos_i_e, v1m, t1, pos_j_s, pos_j_e, v2m, t2);
				//�ŒZ���������v���a�����������Ƃ�
				if (dist_captocap <= add_rad)
				{
					//�ʒu�̍��������߂�
					Vector3D v = pos_j_s - pos_i_s;
					//���K������
					Vector3D norm = v.Normalize();
					//��������x�N�g���̒��������߂�
					double len = v.Length();
					//�x�N�g���̒����ƍ��v���a�̍������߂�
					len = add_rad - len;
					//���K�������ʒu�������x�N�g���̒����ŃX�P�[�����O�����l�����߂�
					Vector3D pos = norm.Scale(len);
					//���������̃R���|�[�l���g�����I�u�W�F�N�g�̈ʒu�ɉ��Z����
					col_j->GetOwner()->SetPos(col_j->GetPos() + pos);
				}
			}
			//�Փ˔���^�C�v������^�C�v�ƃJ�v�Z���^�C�v�̎�
			if (col_i->GetType() == CollisionComponent::COLLISIONTYPE::WEAPON && col_j->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE)
			{
				//�_�C�i�~�b�N�L���X�g�ŕ���^�C�v�̏Փ˔���R���|�[�l���g�̏����擾
				WeaponColComponent* col = dynamic_cast<WeaponColComponent*>(col_i);
				//���g�̎�����Ŕ�����Ƃ��Ȃ��悤�ɃR���|�[�l���g�̃O���[�u�Ŕ��f
				if (col_i->GetGroup() == col_j->GetGroup()) { continue; }
				//�n�_�A�I�_���e�R���|�[�l���g�Őݒ肵���n�_�A�I�_��
				pos_i_s = col->GetPos();
				pos_i_e = col->GetTopPos();
				pos_j_s = col_j->GetPos();
				pos_j_e = col_j->GetPos() + Vector3D(0.0, seg, 0.0);
				//�����Ɛ����̍ŒZ���������߂�
				dist_captocap = MyMath::DisSegAndSeg(pos_i_s, pos_i_e, v1m, t1, pos_j_s, pos_j_e, mHitPos, t2);
				//�ŒZ���������v���a�����������Ƃ�
				if (dist_captocap <= add_rad)
				{
					//���O���[�v���v���C���[�ƓG��������
					if (col_i->GetGroup() == CollisionComponent::COLLISIONGROUP::PLAYER && col_j->GetGroup() == CollisionComponent::COLLISIONGROUP::ENEMY)
					{
						//���U�����̎�
						if (AttackManager::GetInstance()->IsAttack())
						{
							EnemyMob* enemy = dynamic_cast<EnemyMob*>(col_j->GetOwner());
							enemy->Damage(col_i->GetOwner()->GetPos());
						}
					}
				}
			}
		}
	}
}