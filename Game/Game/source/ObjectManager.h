#pragma once
#include "AppFrame.h" 
#include <list>
//�I�u�W�F�N�g�̓o�^�A�����ȂǂɊւ��N���X
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* obInstance;
	void Process();
	void Render();
	//�o�^
	void Spawn(ObjectBase* obj);
	void AddDraw(class DrawComponent* draw);
	void AddBillboard(class DrawBillboardComponent* billboard);
	//����
	void Destroy(ObjectBase* obj);
	//�Q�b�^�[
	std::list<ObjectBase*> GetObjectList() { return mObjectList; }
	//std::list<class DrawComponent*> GetDrawList() { return _drawList; }
	static ObjectManager* GetInstance() { return obInstance; }

protected:
	std::list<ObjectBase*> mObjectList;
	std::list<class DrawComponent*> mDrawList;
	std::list<class DrawBillboardComponent*> mBillboardList;
};

