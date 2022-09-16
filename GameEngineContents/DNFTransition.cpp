#include "PreCompile.h"
#include "DNFTransition.h"

#include <GameEngineBase/GameEngineRandom.h>

DNFTransition::DNFTransition()
{
}

DNFTransition::~DNFTransition()
{
}

void DNFTransition::AddValue(std::string _Name, int _Probability)
{
	//map�� Value�� -1�� �̹� �����ϸ� ����
	if (_Probability == -1)
	{
		for (auto i : RandomValue_)
		{
			if (i.second == -1)
			{
				MsgBoxAssert("�̹� -1�� ���� �����մϴ�.");
			}
		}
	}

	//Ȯ�� ���� 100�� �ʸӰ��� ����
	int Sum = _Probability;
	for (auto i : RandomValue_)
	{
		if (i.second == -1)
		{
			continue;
		}
		Sum += i.second;
	}
	if (Sum > 100)
	{
		MsgBoxAssert("Ȯ�� ������ 100�� �Ѿ�ϴ�.");
	}

	RandomValue_.insert(std::make_pair(_Name, _Probability));
}

bool TransComp(std::pair<std::string, int>& _Left, std::pair<std::string, int>& _Right)
{
	return _Left.second > _Right.second;
}

std::string DNFTransition::Decide()
{
	if (RandomValue_.empty() == true)
	{
		MsgBoxAssert("Map�� ����ֽ��ϴ�.");
	}

	//Map�� �����͸� Vector�� ����ް�, �� Vector�� Value������ �������� ��������.
	std::vector < std::pair<std::string, int> > Vec(RandomValue_.begin(), RandomValue_.end());
	std::sort(Vec.begin(), Vec.end(), TransComp);

	int Value = GameEngineRandom::MainRandom.RandomInt(0, 100);
	int Sum = 0;

	for (int i = 0; i < Vec.size(); i++)
	{
		//���������ε� -1�� ���´ٴ� ���� Ȯ���� �� ���̶�� �̾߱�
		if (Vec[i].second == -1)
		{
			return Vec[i].first;
		}
		Sum += Vec[i].second;
		if (Value < Sum)
		{
			return Vec[i].first;
		}
	}

	MsgBoxAssert("�߸��� Decide");
	return "";
}