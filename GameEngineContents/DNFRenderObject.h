#pragma once
#include <GameEngineCore/GameEngineActor.h>


//�������� ������ ���͵��� �� Ŭ������ ��� �޴´�.
//��������Ʈ ���ҽ��� �� �� Ȱ���ϱ� �����ϰ� �ϱ����� Ŭ����
enum class AttackType
{
	Top,
	Bottom,
	Middle,
};

struct AttackData
{
	std::string AttackName;
	int AttCount;
	AttackType Type;
	int* Att;
	float Stiffness;
	float YForce;
	float XForce;
};


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

	//_Dir�� X������ Flip
	void FlipX(const float4& _Dir)
	{
		if (_Dir.x > 0.0f)
		{
			GetTransform().PixLocalPositiveX();
		}
		else if (_Dir.x < 0.0f)
		{
			GetTransform().PixLocalNegativeX();
		}
	}

	inline float4 GetDirX()
	{
		if (GetTransform().GetLocalScale().x > 0)
		{
			return float4::RIGHT;
		}
		else if (GetTransform().GetLocalScale().x < 0)
		{
			return float4::LEFT;
		}

		return float4::ZERO;
	}

	AttackData CurAttackData_;

protected:

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
	
	//�ȼ��浹 ���� �Լ�
	//�̵���(�̷��� �̵��� ��)�� �ŰԺ�����
	bool CanMove(const float4& _MoveValue);
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
	
	//ü�� ����
	bool OnAir_; //Jump��?
	float GroundYPos_;

	//������
	float Stiffness_;




private:

};

