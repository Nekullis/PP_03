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
	//線分と線分の最短距離を求める際に使う変数。
	Vector3D v1m;
	Vector3D v2m;
	double t1 = 0.0;
	double t2 = 0.0;
	//各衝突判定コンポーネントのプロセス更新
	for (auto&& col : mCollisionList)
	{
		col->Update();
	}
	for (auto&& col_i : mCollisionList)
	{
		for (auto&& col_j : mCollisionList)
		{
			//同じコンポーネントは除外
			if (col_i == col_j) { continue; }
			//合計半径を求めておく
			float add_rad = col_i->GetRadius() + col_j->GetRadius();
			//線分の始点、終点初期化
			Vector3D pos_i_s;
			Vector3D pos_i_e;
			Vector3D pos_j_s;
			Vector3D pos_j_e;
			//どちらも衝突判定タイプがカプセルの場合
			if (col_i->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE && col_j->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE)
			{
				//始点、終点を各コンポーネントで設定した始点、終点に
				pos_i_s = col_i->GetPos();
				pos_i_e = col_i->GetPos() + Vector3D(0.0, seg, 0.0);
				pos_j_s = col_j->GetPos();
				pos_j_e = col_j->GetPos() + Vector3D(0.0, seg, 0.0);
				//線分と線分の最短距離を求める
				dist_captocap = MyMath::DisSegAndSeg(pos_i_s, pos_i_e, v1m, t1, pos_j_s, pos_j_e, v2m, t2);
				//最短距離が合計半径よりも小さいとき
				if (dist_captocap <= add_rad)
				{
					//位置の差分を求める
					Vector3D v = pos_j_s - pos_i_s;
					//正規化する
					Vector3D norm = v.Normalize();
					//差分からベクトルの長さを求める
					double len = v.Length();
					//ベクトルの長さと合計半径の差を求める
					len = add_rad - len;
					//正規化した位置差分をベクトルの長さでスケーリングした値を求める
					Vector3D pos = norm.Scale(len);
					//動かす側のコンポーネントを持つオブジェクトの位置に加算する
					col_j->GetOwner()->SetPos(col_j->GetPos() + pos);
				}
			}
			//衝突判定タイプが武器タイプとカプセルタイプの時
			if (col_i->GetType() == CollisionComponent::COLLISIONTYPE::WEAPON && col_j->GetType() == CollisionComponent::COLLISIONTYPE::CAPSULE)
			{
				//ダイナミックキャストで武器タイプの衝突判定コンポーネントの情報を取得
				WeaponColComponent* col = dynamic_cast<WeaponColComponent*>(col_i);
				//自身の持つ武器で判定をとられないようにコンポーネントのグルーブで判断
				if (col_i->GetGroup() == col_j->GetGroup()) { continue; }
				//始点、終点を各コンポーネントで設定した始点、終点に
				pos_i_s = col->GetPos();
				pos_i_e = col->GetTopPos();
				pos_j_s = col_j->GetPos();
				pos_j_e = col_j->GetPos() + Vector3D(0.0, seg, 0.0);
				//線分と線分の最短距離を求める
				dist_captocap = MyMath::DisSegAndSeg(pos_i_s, pos_i_e, v1m, t1, pos_j_s, pos_j_e, mHitPos, t2);
				//最短距離が合計半径よりも小さいとき
				if (dist_captocap <= add_rad)
				{
					//かつグループがプレイヤーと敵だった時
					if (col_i->GetGroup() == CollisionComponent::COLLISIONGROUP::PLAYER && col_j->GetGroup() == CollisionComponent::COLLISIONGROUP::ENEMY)
					{
						//かつ攻撃中の時
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