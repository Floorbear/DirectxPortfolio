#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include "AvatarManager.h"

#include <GameEngineCore/GameEngineCollision.h>

class VilmarkLevel;
class SeriaRoom;
class Elvenguard;
class Player_Main : public DNFRenderObject
{
	friend AvatarManager;
	friend VilmarkLevel;
	friend DNFHUD;
	friend SeriaRoom;
	friend Elvenguard;
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
		IsAttack_End_ = true;
		AttackCol_->Off();
	}

	int PrevMapPos_; // 0 : ���� �����ʿ��� �����ʿ� �־���, 1: ���� ���ʿ� �־���
	bool IsLevelChanging_ = false; //������ �ٲٰ� �ִ����Դϴ�.
	//�ƹ�Ÿ ���� ������
	AvatarManager AvatarManager_;

	//��Ʋ��� ����
	bool IsBattleMode_ = false;
	inline void OnBattleMode()
	{
		IsBattleMode_ = true;
	}
	inline void OffBattleMode()
	{
		IsBattleMode_ = false;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	//void LevelStartEvent() override
	//{
	//}

private:

	//���� ����
	void AutoAttackSound();
public:
	std::string GetRandomSound(std::string _SoundBase, int _Min, int _Max);
private:
	//ī�޶� ����
	void ChaseCamera(float _DeltaTime);

	//�ȼ��浹 üũ
	void CheckColMap();

	//ĳ������ �浹ü �ʱ�ȭ
	void InitCol();

	//ĳ������ ������Ʈ �ʱ�ȭ
	void InitState();

	//ĳ������ �ִϸ��̼� �Լ� �ʱ�ȭ
	void InitAniFunc();

	void TripleSlashAniFunc();

	void ExtremOverkillAniFunc();

	void OutragebreakAniFunc();

	void Frenzy_AutoAttackAniFunc();

	void AutoAttackAniFunc();

	void HopSmashAniFunc();

	void UpperSlashAniFunc();

	void GoreCrossAniFun();

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

	//ī�޶� ��鸲����
public:
	inline void ShakeCamera(float _Size, float _Duration, float _IterTime = 0.04f)
	{
		ShakeIterTimer_.StartTimer(_IterTime);
		ShakeDurationTimer_.StartTimer(_Duration);
		ShakeSize_ = _Size;
	}
protected:
	float4 UpdateShakeCamera(float _DeltaTime);
	float4 ShakeData_;
	Timer ShakeIterTimer_;
	Timer ShakeDurationTimer_;
	float ShakeSize_ = 0.f;

private:
	Timer* CreateSkillCoolTime(std::string _Name, float Time_); //���ο� ��ų��Ÿ���� ���� �����Ѵ�.
	void InitSkillCoolTime(); //���� ��ų��Ÿ�ӵ��� �ʱ�ȭ �Ѵ�.
	void CoolTimeUpdate(float _DeltaTime); //��ų ��Ÿ���� ������Ʈ�Ѵ�.

	//���ݰ���
	GameEngineCollision* AttackCol_;
	GameEngineCollision* BottomAttackCol_;
	int AttackCount_;
	void AttackEnd();
public:
	int CalAtt(int _Value);	//���� ������ ���ݷ� ���
private:

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

	void ChangeDelayMotion(PlayerAnimations _Motion)
	{
		AvatarManager_.ChangeMotion(_Motion);
	}

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

	//��Ȱ ���� ����
	GameEngineTextureRenderer* Resurrection_ = nullptr;

	//������ ���� ����
	bool IsFrenzy_ = false;
	float FrenzyXForce = 35.f;
	float FrenzyStif = 0.07f;
	float FrenzyRStif = 0.055f;
	GameEngineTextureRenderer* Frenzy_Upper_ = nullptr;
	GameEngineTextureRenderer* Frenzy_Under_ = nullptr;
	GameEngineTextureRenderer* Frenzy_Trail_ = nullptr;
	GameEngineTextureRenderer* Blood_Effect_ = nullptr;

	//�Ϳ�ų ����
	GameEngineTextureRenderer* EOKRenderer_ = nullptr;
	GameEngineTextureRenderer* EOKRenderer_Dodge_ = nullptr;

	//�ƿ��� ����
	GameEngineTextureRenderer* Outragebreak_Sword_ = nullptr;
	bool IsOutragebreak_first_ = true;

	//�ܰ�������
	Timer TripleSlashTimer_ = Timer();
	float TripleSlashGetKeyTime_ = 0.5f;
	float TripleSlashForceX = 450.0f;
	GameEngineTextureRenderer* TripleSlash_ = nullptr;
	GameEngineTextureRenderer* TripleSlash_Trail_ = nullptr;

	void AddRenderer_Init();

	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo _Info);

	void MoveStart(const StateInfo _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo _Info);

	void JumpStart(const StateInfo _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo _Info);
	void JumpEnd(const StateInfo _Info);

	void JumpLogicEnd();

	void AirborneStart(const StateInfo _Info);
	void AirborneUpdate(float _DeltaTime, const StateInfo _Info);

	void DownStart(const StateInfo _Info);
	void DownUpdate(float _DeltaTime, const StateInfo _Info);

	void QuickStandingStart(const StateInfo _Info);
	void QuickStandingUpdate(float _DeltaTime, const StateInfo _Info);
	void  QuickStandingEnd(const StateInfo _Info);

	void AutoAttackStart(const StateInfo _Info);
	void AutoAttackUpdate(float _DeltaTime, const StateInfo _Info);
	void AutoAttackEnd(const StateInfo _Info);

	void UpperSlashStart(const StateInfo _Info);
	void UpperSlashUpdate(float _DeltaTime, const StateInfo _Info);
	void UpperSlashEnd(const StateInfo _Info);

	void TripleSlashStart(const StateInfo _Info);
	void TripleSlashUpdate(float _DeltaTime, const StateInfo _Info);
	void TripleSlashEnd(const StateInfo _Info);

	void HopSmashStart(const StateInfo _Info);
	void HopSmashUpdate(float _DeltaTime, const StateInfo _Info);
	void HopSmashEnd(const StateInfo _Info);

	void OutragebreakStart(const StateInfo _Info);
	void OutragebreakUpdate(float _DeltaTime, const StateInfo _Info);
	void OutragebreakEnd(const StateInfo _Info);

	void ExtremOverkillStart(const StateInfo _Info);
	void ExtremOverkillUpdate(float _DeltaTime, const StateInfo _Info);
	void ExtremOverkillEnd(const StateInfo _Info);

	void GoreCrossStart(const StateInfo _Info);
	void GoreCrossUpdate(float _DeltaTime, const StateInfo _Info);
	void GoreCrossEnd(const StateInfo _Info);

	void FrenzyStart(const StateInfo _Info);
	void FrenzyUpdate(float _DeltaTime, const StateInfo _Info);

	void FuryStart(const StateInfo _Info);
	void FuryUpdate(float _DeltaTime, const StateInfo _Info);

	void HitStart(const StateInfo _Info);
	void HitUpdate(float _DeltaTime, const StateInfo _Info);

	void DieStart(const StateInfo _Info);
	void DieUpdate(float _DeltaTime, const StateInfo _Info);

	//DefaultValues
	void InitDefaultValue();
	struct DefaultValue
	{
		//��& �߷� & ������
		float DefaultFriction = 700.0f;
		float DefaultGravity = 700.0f;

		float HopSmashGravity = 1200.0f;
		float HopSmashFriction = 1200.0f;

		//Pos&Scale
		float4 HitAbovePos;
		float4 HitAboveScale;
		float4 HitBelowPos;
		float4 HitBelowScale;
		float4 AutoAttackPos;
		float4 AutoAttackScale;
		float4 UpperSlashPos;
		float4 UpeerSlashScale;
		float4 TripleSlashhPos = float4(20, -45, -500);
		float4 TripleSlashhScale = float4(180, 100, 1);
		float4 HopSmashScale = float4(230, 140, 1);;
		float4 GoreCrossPos;
		float4 GoreCrossScale;

		float4 OutrageBreakPos = float4(145, -45, -500);
		float4 OutrageBreakScale = float4(420, 180, 1);

		float4 ExtremOverKillPos = float4(290, 0, -500);
		float4 ExtremOverKillScale = float4(470, 350, 1);

		float4 SuperArmorPos;
		float4 SuperArmorScale;

		float4 GoreCrossSpawnPos = { 50,-23,0 };
		float SuperArmorMul;

		//���ݷ�
		int UpperSlashAtt;
		int AutoAttackAtt;
		int FrenzyAtt = 5000;
		int GoreCrossAtt = 15000;
		int OutrageBreakAtt = 35000;

		//����, ü��
		int Default_HP = 30000;//30000
		int Default_MP = 20000;

		//���� �Һ�
		int UpperSlash_MP = 70;
		int GoreCross_MP = 120;
		int HopSmash_MP = 120;
		int Fury_MP = 100;
		int Outragebreak_MP = 400;

		float Down_Time = 1.3f;
		float Down_God_Time = 0.48f;
	};
public:
	DefaultValue Value_;
};
