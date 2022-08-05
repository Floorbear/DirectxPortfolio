#pragma once
#include <GameEngineCore/GameEngineActor.h>


//�������� ������ ���͵��� �� Ŭ������ ��� �޴´�.
//��������Ʈ ���ҽ��� �� �� Ȱ���ϱ� �����ϰ� �ϱ����� Ŭ����
class DNFLevel;
class DNFRenderObject : public GameEngineActor
{
	friend class DNFLevel;
public:
	DNFRenderObject();
	~DNFRenderObject();


	DNFRenderObject(const DNFRenderObject& _Other) = delete;
	DNFRenderObject(const DNFRenderObject&& _Other) noexcept = delete;
	DNFRenderObject& operator=(const DNFRenderObject& _Ohter) = delete;
	DNFRenderObject& operator=(const DNFRenderObject&& _Other) noexcept = delete;

	DNFLevel* GetDNFLevel();


protected:
	GameEngineTextureRenderer* MainRenderer_;
	
	//������ �ȵȰ��� üũ �� �ִ� �Լ�
	void ErrorCheck();

	//Update���� ȣ��
	//�ϴ� ����
	//1. ���� üũ
	void DNFUpdate();

	//start���� ȣ��
	//�ϴ� ����
	//1. MainRenderer ����
	virtual void DNFStart();

	bool IsStart_; //DnfStart ȣ���߳�
private:

};

