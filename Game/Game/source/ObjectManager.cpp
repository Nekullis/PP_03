#include "ObjectManager.h"
#include "DrawComponent.h"
#include "DrawBillboardComponent.h"
ObjectManager* ObjectManager::obInstance = nullptr;
ObjectManager::ObjectManager()
{
	obInstance = this;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Spawn(ObjectBase* obj)
{
	//コンテナへオブジェクトを入れる
	mObjectList.emplace_back(obj);
}

void ObjectManager::AddDraw(DrawComponent* draw)
{
	mDrawList.emplace_back(draw);
}

void ObjectManager::AddBillboard(DrawBillboardComponent* billboard)
{
	mBillboardList.emplace_back(billboard);
}

void ObjectManager::Destroy(ObjectBase* obj)
{
	//コンテナ内のオブジェクトの削除
	mObjectList.remove(obj);
	delete obj;
}

void ObjectManager::Process()
{
	//一時的なコンテナの作成
	std::list<ObjectBase*> temp_remove;
	for (auto&& object : mObjectList)
	{
		//オブジェクトのプロセス
		object->Process();
		//消去フラグがtrueになったならそのオブジェクトを一時的なコンテナに入れる
		if (object->GetState() == ObjectBase::State::DEAD) { temp_remove.push_back(object); }
	}
	//一時的なコンテナの中身を削除する
	for (auto&& object : temp_remove)
	{
		Destroy(object);
	}
}

void ObjectManager::Render()
{
	//登録されているオブジェクトの描画
	for (auto&& draw : mDrawList)
	{
		draw->Update();
	}
	for (auto&& billboard : mBillboardList)
	{
		billboard->Update();
	}
}
