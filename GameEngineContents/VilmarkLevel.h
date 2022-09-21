#pragma once
#include "DNFLevel.h"
#include "DNFMath.h"

class VilmarkMap;
class DNFMonster;
class VilmarkLevel : public DNFLevel
{
public:
	VilmarkLevel();
	~VilmarkLevel();

	VilmarkLevel(const VilmarkLevel& _Other) = delete;
	VilmarkLevel(const VilmarkLevel&& _Other) noexcept = delete;
	VilmarkLevel& operator=(const VilmarkLevel& _Ohter) = delete;
	VilmarkLevel& operator=(const VilmarkLevel&& _Other) noexcept = delete;

	template <typename MonsterType>
	MonsterType* CreateMonster(float4 _SpawnWorldPos)
	{
		DNFMonster* NewMonster = CreateActor< MonsterType>();
		NewMonster->GetTransform().SetWorldPosition(_SpawnWorldPos);

		//ID �Ҵ� && MonsterList�� �־��ֱ�
		if (MonsterList_.empty() == true) //���� ������ ���Ͱ� �ƿ� ���°��
		{
			int ID = 1;
			NewMonster->ID_ = ID;
			MonsterList_.insert(std::make_pair(ID, NewMonster));
			return dynamic_cast<MonsterType*>(NewMonster);
		}

		std::map<int, DNFMonster*>::iterator StartIter = MonsterList_.begin();
		for (int i = 1; i <= MonsterList_.size(); i++)
		{
			if (i == MonsterList_.size()) //�������� �����ϴ°��
			{
				int ID = i + 1;
				NewMonster->ID_ = ID;
				MonsterList_.insert(std::make_pair(ID, NewMonster));
				break;
			}
			if (i == StartIter->first)
			{
				StartIter++;
				continue;
			}
			else
			{
				int ID = i;
				NewMonster->ID_ = ID;
				MonsterList_.insert(std::make_pair(ID, NewMonster));
				break;
			}
		}
		return dynamic_cast<MonsterType*>(NewMonster);
	}

protected:
	int StageNumber_ = -1; //���° �������� �˷��� (���ó : �����̵��Ҷ� ��ȣ��)
	void VilmarkStart();
	void VilmarkUpdate(float _DeltaTime);

	void Update_Door(float _DeltaTime);

	void VilmarkStartLevel();

	VilmarkMap* VilmarkMap_;

	Timer LevelChangeTimer_;
	std::map<int, DNFMonster*> MonsterList_;
};
