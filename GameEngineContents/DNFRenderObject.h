#pragma once
#include <GameEngineCore/GameEngineActor.h>

//�������� ������ ���͵��� �� Ŭ������ ��� �޴´�.
//��������Ʈ ���ҽ��� �� �� Ȱ���ϱ� �����ϰ� �ϱ����� Ŭ����
class DNFRenderObject : public GameEngineActor
{
public:
	DNFRenderObject();
	~DNFRenderObject();


	DNFRenderObject(const DNFRenderObject& _Other) = delete;
	DNFRenderObject(const DNFRenderObject&& _Other) noexcept = delete;
	DNFRenderObject& operator=(const DNFRenderObject& _Ohter) = delete;
	DNFRenderObject& operator=(const DNFRenderObject&& _Other) noexcept = delete;

protected:
	GameEngineTextureRenderer* MainRenderer_;
	
	//������ �ȵȰ��� üũ �� �ִ� �Լ�
	void ErrorCheck();

	//�ϴ� ����
	//1. ���� üũ
	void DNFUpdate();

	//�ϴ� ����
	//1. MainRenderer ����
	void DNFStart();

private:
	bool IsStart_; //DnfStart ȣ���߳�

};

