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
	//�R���e�i�փI�u�W�F�N�g������
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
	//�R���e�i���̃I�u�W�F�N�g�̍폜
	mObjectList.remove(obj);
	delete obj;
}

void ObjectManager::Process()
{
	//�ꎞ�I�ȃR���e�i�̍쐬
	std::list<ObjectBase*> temp_remove;
	for (auto&& object : mObjectList)
	{
		//�I�u�W�F�N�g�̃v���Z�X
		object->Process();
		//�����t���O��true�ɂȂ����Ȃ炻�̃I�u�W�F�N�g���ꎞ�I�ȃR���e�i�ɓ����
		if (object->GetState() == ObjectBase::State::DEAD) { temp_remove.push_back(object); }
	}
	//�ꎞ�I�ȃR���e�i�̒��g���폜����
	for (auto&& object : temp_remove)
	{
		Destroy(object);
	}
}

void ObjectManager::Render()
{
	//�o�^����Ă���I�u�W�F�N�g�̕`��
	for (auto&& draw : mDrawList)
	{
		draw->Update();
	}
	for (auto&& billboard : mBillboardList)
	{
		billboard->Update();
	}
}
