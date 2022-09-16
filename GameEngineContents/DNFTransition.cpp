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
	//map에 Value가 -1이 이미 존재하면 오류
	if (_Probability == -1)
	{
		for (auto i : RandomValue_)
		{
			if (i.second == -1)
			{
				MsgBoxAssert("이미 -1의 값이 존재합니다.");
			}
		}
	}

	//확률 합이 100이 너머가면 오류
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
		MsgBoxAssert("확률 총합이 100이 넘어갑니다.");
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
		MsgBoxAssert("Map이 비어있습니다.");
	}

	//Map의 데이터를 Vector에 복사받고, 그 Vector을 Value순으로 내림차순 정렬하자.
	std::vector < std::pair<std::string, int> > Vec(RandomValue_.begin(), RandomValue_.end());
	std::sort(Vec.begin(), Vec.end(), TransComp);

	int Value = GameEngineRandom::MainRandom.RandomInt(0, 100);
	int Sum = 0;

	for (int i = 0; i < Vec.size(); i++)
	{
		//내림차순인데 -1이 나온다는 것은 확률의 맨 끝이라는 이야기
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

	MsgBoxAssert("잘못된 Decide");
	return "";
}