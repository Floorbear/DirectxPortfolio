#pragma once

class DNFTransition
{
public:
	DNFTransition();
	~DNFTransition();

	void AddValue(std::string _Name, int _Probability);//_Probability�� -1�̸� ���Ȯ���� ���ϰ� ������ ���� ��., -1�� ���� 2���̻� ������� �� ����
	//void ModifyValue();
	//void DeleteValue();
	std::string Decide();
private:
	std::map<std::string, int> RandomValue_;
};
