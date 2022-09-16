#pragma once

class DNFTransition
{
public:
	DNFTransition();
	~DNFTransition();

	void AddValue(std::string _Name, int _Probability);//_Probability가 -1이면 모든확률을 다하고 나머지 값이 됨., -1의 값을 2개이상 들고있을 수 없음
	//void ModifyValue();
	//void DeleteValue();
	std::string Decide();
private:
	std::map<std::string, int> RandomValue_;
};
