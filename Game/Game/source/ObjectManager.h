#pragma once
#include "AppFrame.h" 
#include <list>
//オブジェクトの登録、消去などに関わるクラス
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* obInstance;
	void Process();
	void Render();
	//登録
	void Spawn(ObjectBase* obj);
	void AddDraw(class DrawComponent* draw);
	void AddBillboard(class DrawBillboardComponent* billboard);
	//消去
	void Destroy(ObjectBase* obj);
	//ゲッター
	std::list<ObjectBase*> GetObjectList() { return mObjectList; }
	//std::list<class DrawComponent*> GetDrawList() { return _drawList; }
	static ObjectManager* GetInstance() { return obInstance; }

protected:
	std::list<ObjectBase*> mObjectList;
	std::list<class DrawComponent*> mDrawList;
	std::list<class DrawBillboardComponent*> mBillboardList;
};

