#pragma once
#include "AppFrame.h"

class ModeGame : public ModeBase
{
public:
	static ModeGame* gameInstance;
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void Register();
	//ゲッター
	static ModeGame* GetInstance() { return gameInstance; }
	class ObjectManager* GetManager() { return mObjManager; }
	//セッター
	void SetClearFlag(bool flag) { mGameClearFlag = flag; }
protected:
	class ObjectManager* mObjManager;
	class GameCollision* mGameCol;
	class CollisionManager* mColManager;
	class DamageEffect* mDamageEffect;
	class Player* mPlayer;
	class EnemyMob* mEnemy;
	class Stage* mStage;
	bool mGameClearFlag;
};

