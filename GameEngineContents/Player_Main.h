#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include "AvatarManager.h"

#include <GameEngineCore/GameEngineCollision.h>

class Player_Main : public DNFRenderObject
{
	friend AvatarManager;
public:
	Player_Main();
	~Player_Main();

	Player_Main(const Player_Main& _Other) = delete;
	Player_Main(const Player_Main&& _Other) noexcept = delete;
	Player_Main& operator=(const Player_Main& _Ohter) = delete;
	Player_Main& operator=(const Player_Main&& _Other) noexcept = delete;

	//�� ����ī��Ʈ << ���Ͱ� ���� ������ ������ �´� ���� ����
	int GetAttackCount()
	{
		return AttackCount_;
	}

	inline float GetStiffness() //��ų�� �÷��̾��� ������ �˾ƾ��ϴ³� ������
	{
		return Stiffness_;
	}

	inline float4 GetBotPos()
	{
		if (OnAir_ == true)
		{
			float4 DownPos = GetTransform().GetWorldPosition();
			DownPos.y = GroundYPos_ + BotPos_.y;
			return DownPos;
		}
		else
		{
			float4 DownPos = GetTransform().GetWorldPosition();
			DownPos.y += BotPos_.y;
			return DownPos;
		}
	}

	inline AttackData& GetAttData()
	{
		return CurAttackData_;
	}
	inline GameEngineTransform& GetAttColTrans()
	{
		return AttackCol_->GetTransform();
	}
	inline void CurAttEnd()
	{
		IsReadyNextAttack_ = false;
		IsAttack_End_ = true;
	}
	//�ƹ�Ÿ ���� ������
	AvatarManager AvatarManager_;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	//ī�޶� ����
	void ChaseCamera();

	//�ȼ��浹 üũ
	void CheckColMap();

	//ĳ������ �浹ü �ʱ�ȭ
	void InitCol();

	//ĳ������ ������Ʈ �ʱ�ȭ
	void InitState();

	//ĳ������ �ִϸ��̼� �Լ� �ʱ�ȭ
	void InitAniFunc();

	void SetAttackCol(const float4& _Pos, const float4& _Scale); //Col On & Set
	//���� ����Ű�� ���Է� �޴´�.
	// ���� ������ �ִϸ��̼��� Enum���� �˾ƿ���, ���� ������ �ִٴ� bool�� true�� ��ȯ, �� ����� bool�� return
	bool CheckAttackKey();

	bool CheckCanUsingSkill(std::string _SkillName, PlayerAnimations _ChangeStateEnum);

	//Hit����
	Timer Hit_Timer_;

	//��Ÿ�� ����
	std::map<std::string, Timer*> SkillCoolTime_;
public:
	std::map<std::string, Timer*> GetSkillCoolTimeList()
	{
		return SkillCoolTime_;
	}
private:
	Timer* CreateSkillCoolTime(std::string _Name, float Time_); //���ο� ��ų��Ÿ���� ���� �����Ѵ�.
	void InitSkillCoolTime(); //���� ��ų��Ÿ�ӵ��� �ʱ�ȭ �Ѵ�.
	void CoolTimeUpdate(float _DeltaTime); //��ų ��Ÿ���� ������Ʈ�Ѵ�.

	//���ݰ���
	GameEngineCollision* AttackCol_;
	GameEngineCollision* BottomAttackCol_;
	int AttackCount_;
	void AttackEnd();
	int CalAtt(int _Value);	//���� ������ ���ݷ� ���

	bool  IsAttack_End_; //"�ϴ�" ���� 1ȸ�� ������ IsAttack_End == true > ���� ReadyNextAttack �б⿡ ����
	bool IsReadyNextAttack_;
	PlayerAnimations NextAttackAni_; // ���Է� �޾Ƽ� ������ ������ �ൿ

	//����
	int CurMP_;
	int MaxMP_;
	std::map<std::string, int> MPConsumption_;
public:
	inline int GetMaxMP()
	{
		return MaxMP_;
	}
	inline int GetCurMP()
	{
		return CurMP_;
	}
private:

	//UI
	GameEngineUIRenderer* UIRenderer_;

	//�ƹ�Ÿ
	GameEngineTextureRenderer* HairRenderer_a_;
	GameEngineTextureRenderer* HairRenderer_d_;
	GameEngineTextureRenderer* WeaponRenderer_b_;
	GameEngineTextureRenderer* WeaponRenderer_c_;

	GameEngineTextureRenderer* PantsRenderer_a_;
	GameEngineTextureRenderer* PantsRenderer_b_;
	GameEngineTextureRenderer* PantsRenderer_d_;

	GameEngineTextureRenderer* CoatRenderer_a_;
	GameEngineTextureRenderer* CoatRenderer_b_;
	GameEngineTextureRenderer* CoatRenderer_c_;
	GameEngineTextureRenderer* CoatRenderer_d_;

	GameEngineTextureRenderer* ShoesRenderer_a_;
	GameEngineTextureRenderer* ShoesRenderer_b_;

	GameEngineTextureRenderer* BeltRenderer_c_;
	GameEngineTextureRenderer* BeltRenderer_d_;

	GameEngineTextureRenderer* CapRenderer_a_;
	GameEngineTextureRenderer* CapRenderer_b_;
	GameEngineTextureRenderer* CapRenderer_c_;

	//���۾Ƹ� & �ܻ�
	std::vector<GameEngineTextureRenderer*> AllCopyRenderer_;
	float4 SuperArmorScale_;
	float SuperArmorMulTime_;
	void StartSuperArmor(float _SuperArmorTime);
	void CopyRendererUpdate(float _DeltaTime);

	//���� ���� ����Ű�� ���� ���� �ƹ�Ű�� ������ ������ float4::zero����
	float4 GetMoveDir();

	//Flip�� �Ȼ��³� �ƴϳ�
	bool IsDirXPositive();

	bool IsPressMoveKey();

	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo _Info);

	void MoveStart(const StateInfo _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo _Info);

	void JumpStart(const StateInfo _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo _Info);
	void JumpEnd(const StateInfo _Info);

	void AirborneStart(const StateInfo _Info);
	void AirborneUpdate(float _DeltaTime, const StateInfo _Info);

	void DownStart(const StateInfo _Info);
	void DownUpdate(float _DeltaTime, const StateInfo _Info);

	void AutoAttackStart(const StateInfo _Info);
	void AutoAttackUpdate(float _DeltaTime, const StateInfo _Info);
	void AutoAttackEnd(const StateInfo _Info);

	void UpperSlashStart(const StateInfo _Info);
	void UpperSlashUpdate(float _DeltaTime, const StateInfo _Info);
	void UpperSlashEnd(const StateInfo _Info);

	void GoreCrossStart(const StateInfo _Info);
	void GoreCrossUpdate(float _DeltaTime, const StateInfo _Info);
	void GoreCrossEnd(const StateInfo _Info);

	void HitStart(const StateInfo _Info);
	void HitUpdate(float _DeltaTime, const StateInfo _Info);

	//DefaultValues
	void InitDefaultValue();
	struct DefaultValue
	{
		//Pos&Scale
		float4 HitAbovePos;
		float4 HitAboveScale;
		float4 HitBelowPos;
		float4 HitBelowScale;
		float4 AutoAttackPos;
		float4 AutoAttackScale;
		float4 UpperSlashPos;
		float4 UpeerSlashScale;
		float4 GoreCrossPos;
		float4 GoreCrossScale;

		float4 SuperArmorPos;
		float4 SuperArmorScale;

		float4 GoreCrossSpawnPos = { 50,-23,0 };
		float SuperArmorMul;

		//���ݷ�
		int UpperSlashAtt;
		int AutoAttackAtt;
		int GoreCrossAtt = 15000;

		//����, ü��
		int Default_HP = 30000;
		int Default_MP = 15000;

		//���� �Һ�
		int UpperSlash_MP = 250;
		int GoreCross_MP = 500;

		float Down_Time = 1.3f;
		float Down_God_Time = 0.48f;
	};
	DefaultValue Value_;
};
