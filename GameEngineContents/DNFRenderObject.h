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

	//�ð����� �����̳�
	std::map<std::string, float> CurTime_; //������ DeltaTime�� �����ϴ� �����̳�
	std::map<std::string, float> DefaultTime_; //ó�� Set�� Time�� �����ϴ� �����̳� , �����Ǵ� Time�� Random�� �ִ� ����
	std::map<std::string, float> FloatValue_; //�̵��ӵ�, ��Ÿ� ���� ������ �����̳�

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* ShadowRenderer_;

	//shadow���� �Լ�& ����
	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeDNFAnimation(const std::string& _Name);
	void ShadowUpdate();

	float4 ShadowPos_;
	float4 ShadowRot_;

	float4 PrevPos_;

	GameEngineCollision* BotCol_;
	float4 BotPos_;
	
	//������ �ȵȰ��� üũ �� �ִ� �Լ�
	void ErrorCheck();

	//Update���� ȣ��
	//�ϴ� ����
	//1. ���� üũ
	//2. Shadow������Ʈ
	void DNFUpdate();

	//start���� ȣ��
	//�ϴ� ����
	//1. MainRenderer ����
	virtual void DNFStart();


	//Update���� ���������
	void ZSort();

	bool IsStart_; //DnfStart ȣ���߳�

private:

};

