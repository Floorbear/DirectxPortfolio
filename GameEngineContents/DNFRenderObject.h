#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"
#include "DNFGlobalValue.h"


//�������� ������ ���͵��� �� Ŭ������ ��� �޴´�.
//��������Ʈ ���ҽ��� �� �� Ȱ���ϱ� �����ϰ� �ϱ����� Ŭ����
enum class AttackType
{
	Above,
	Below
};

struct AttackData
{
	int ZPos = 0; // ZPos == 0 > ������ Z���� ������ ���� �ʴ´�. 
	std::string AttackName = "";
	int AttCount = 0;
	int MaxAttCount = 10;
	AttackType Type = AttackType::Above;
	Effect AttEffect = Effect::None;
	int Att = 0;
	bool IsCritical = false;
	float Stiffness = 0.f; //����
	float RStiffness =0.0f; //������
	float YForce =0.f;
	float XForce =0.f;
};

struct ScaleNPos
{
	float4 Scale;
	float4 Pos;
};


class DNFLevel;
class Timer;
class EffectActor;
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

	inline	int GetMaxHP()
	{
		return MaxHP_;
	}
	inline int GetCurHP()
	{
		return CurHP_;
	}

	AttackData CurAttackData_;

protected:
	//�ȼ��浹 ���� �Լ�
	//�̵���(�̷��� �̵��� ��)�� �ŰԺ�����
	bool CanMove(const float4& _MoveValue);

	//������ �ȵȰ��� üũ �� �ִ� �Լ�
	void ErrorCheck();

	//Update���� ȣ��
	void DNFUpdate();

	//start���� ȣ��
	virtual void DNFStart();

	//Update���� ���������
	void ZSort();

	virtual void HPBarUpdate(){}; //(���ݴ�����) �� Ŭ������ ��ӹ��� ������ HPBarUpdate�� ���� �Լ�

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* ShadowRenderer_;
	std::list< GameEngineTextureRenderer**> AllDNFRenderer_;

	//shadow���� �Լ�& ����
	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeDNFAnimation(const std::string& _Name);
	void ResetDNFAnimation();
	void ShadowUpdate();

	float4 ShadowPos_;
	float4 ShadowRot_;

	float4 PrevPos_;
	float4 BotPos_;
	GameEngineCollision* BotCol_;


	bool IsStart_; //DnfStart ȣ���߳�

	//Fsm����
	GameEngineStateManager StateManager_;

	//��,�߷� ����
	Force Force_;
	
	//ü�� ����
	bool OnAir_; //Jump��?
	float AirborneTime_;
	float GroundYPos_;

	//���� ����
	float Stiffness_;
	void GiveAndRecevieStiffness(AttackData& _Data, DNFRenderObject* _Other); //�ǰ��ڰ� ȣ��, ������ ����������
	void StiffnessUpdate(float& _DeltaTime); 	//���� ������Ʈ, Update������ �ֿ켱������ ȣ��

	//���� ����
	Timer GodTime_;


	//ü�°���
	int MaxHP_;	//�ִ� ü��
	int CurHP_;	//���� ü��
	void CalHP(int _Value); //_Value�� ��ŭ ü���� ���ϰų� ����.



	//Hit����
	AttackData PrevHitData_; //���� ��� Hit�� Attack�� ����
	GameEngineCollision* HitAbove_;
	GameEngineCollision* HitBelow_;
	float4 DamageFontMovePos_;
	void SetDamageFont(int _Value, float4 _WorldPos, bool IsCritical);
	void HitColCheck(ColOrder _Order); //ȣ���� Monster�� _Oter���� PlayerAttack�� ��
	bool HitCheck(AttackType _Type, DNFRenderObject* _Other);//�Ķ���� : Ȯ���� ���� Ÿ��
	bool AboveHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);
	bool BelowHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);
	bool IsZPosHit(int _ZPos);

	//���۾Ƹ� ����
	bool IsSuperArmor_;
	Timer SuperArmorTimer_;

	//����Ʈ ����
	EffectActor* SetEffect(Effect _Effect, float4 _Pos, float4 _Dir = float4::ZERO);
	float4 HitEffectMovePos_;

private:

};

