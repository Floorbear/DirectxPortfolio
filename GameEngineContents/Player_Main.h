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

	//내 공격카운트 << 몬스터가 같은 공격을 여러번 맞는 것을 방지
	int GetAttackCount()
	{
		return AttackCount_;
	}

	inline float GetStiffness() //스킬등 플레이어의 경직을 알아야하는놈 때문에
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

	int PrevMapPos_; // 0 : 나는 이전맵에서 오른쪽에 있었다, 1: 나는 왼쪽에 있었다
	bool IsLevelChanging_ = false; //레벨을 바꾸고 있는중입니다.
	//아바타 관련 변수들
	AvatarManager AvatarManager_;

	//배틀모드 관련
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

	//사운드 관련
	void AutoAttackSound();
public:
	std::string GetRandomSound(std::string _SoundBase, int _Min, int _Max);
private:
	//카메라 추적
	void ChaseCamera(float _DeltaTime);

	//픽셀충돌 체크
	void CheckColMap();

	//캐릭터의 충돌체 초기화
	void InitCol();

	//캐릭터의 스테이트 초기화
	void InitState();

	//캐릭터의 애니메이션 함수 초기화
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
	//다음 공격키를 선입력 받는다.
	// 다음 공격의 애니메이션을 Enum으로 알아오고, 다음 공격이 있다는 bool을 true로 변환, 그 결과를 bool로 return
	bool CheckAttackKey();

	bool CheckCanUsingSkill(std::string _SkillName, PlayerAnimations _ChangeStateEnum);

	//Hit관련
	Timer Hit_Timer_;

	//쿨타임 관련
	std::map<std::string, Timer*> SkillCoolTime_;
public:
	std::map<std::string, Timer*> GetSkillCoolTimeList()
	{
		return SkillCoolTime_;
	}

	//카메라 흔들림관련
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
	Timer* CreateSkillCoolTime(std::string _Name, float Time_); //새로운 스킬쿨타임을 새로 생성한다.
	void InitSkillCoolTime(); //여러 스킬쿨타임들을 초기화 한다.
	void CoolTimeUpdate(float _DeltaTime); //스킬 쿨타임을 업데이트한다.

	//공격관련
	GameEngineCollision* AttackCol_;
	GameEngineCollision* BottomAttackCol_;
	int AttackCount_;
	void AttackEnd();
public:
	int CalAtt(int _Value);	//현재 공격의 공격력 계산
private:

	bool  IsAttack_End_; //"일단" 공격 1회가 끝나면 IsAttack_End == true > 이후 ReadyNextAttack 분기에 따라
	bool IsReadyNextAttack_;
	PlayerAnimations NextAttackAni_; // 선입력 받아서 다음에 공격할 행동

	//마나
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

	//아바타
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

	//슈퍼아머 & 잔상
	std::vector<GameEngineTextureRenderer*> AllCopyRenderer_;
	float4 SuperArmorScale_;
	float SuperArmorMulTime_;
	void StartSuperArmor(float _SuperArmorTime);
	void CopyRendererUpdate(float _DeltaTime);

	//내가 누른 방향키의 값을 리턴 아무키도 누르지 않으면 float4::zero리턴
	float4 GetMoveDir();

	//Flip이 된상태냐 아니냐
	bool IsDirXPositive();

	bool IsPressMoveKey();

	//부활 상태 관련
	GameEngineTextureRenderer* Resurrection_ = nullptr;

	//프렌지 상태 관련
	bool IsFrenzy_ = false;
	float FrenzyXForce = 35.f;
	float FrenzyStif = 0.07f;
	float FrenzyRStif = 0.055f;
	GameEngineTextureRenderer* Frenzy_Upper_ = nullptr;
	GameEngineTextureRenderer* Frenzy_Under_ = nullptr;
	GameEngineTextureRenderer* Frenzy_Trail_ = nullptr;
	GameEngineTextureRenderer* Blood_Effect_ = nullptr;

	//익오킬 관련
	GameEngineTextureRenderer* EOKRenderer_ = nullptr;
	GameEngineTextureRenderer* EOKRenderer_Dodge_ = nullptr;

	//아웃뷁 관련
	GameEngineTextureRenderer* Outragebreak_Sword_ = nullptr;
	bool IsOutragebreak_first_ = true;

	//단공참관련
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
		//힘& 중력 & 마찰력
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

		//공격력
		int UpperSlashAtt;
		int AutoAttackAtt;
		int FrenzyAtt = 5000;
		int GoreCrossAtt = 15000;
		int OutrageBreakAtt = 35000;

		//마나, 체력
		int Default_HP = 30000;//30000
		int Default_MP = 20000;

		//마나 소비량
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
