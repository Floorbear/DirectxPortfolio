#pragma once
#include "DNFRenderObject.h"
#include "DNFMath.h"
#include "AvatarManager.h"

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

	//내 공격카운트 << 몬스터가 같은 공격을 여러번 맞는 것을 방지
	int GetAttackCount()
	{
		return AttackCount_;
	}
	//아바타 관련 변수들
	AvatarManager AvatarManager_;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	//카메라 추적
	void ChaseCamera();

	//픽셀충돌 체크
	void CheckColMap();

	//캐릭터의 충돌체 초기화
	void InitCol();

	//캐릭터의 스테이트 초기화
	void InitState();

	//캐릭터의 애니메이션 함수 초기화
	void InitAniFunc();

	void SetAttackCol(const float4& _Pos, const float4& _Scale); //Col On & Set
	//다음 공격키를 선입력 받는다.
	// 다음 공격의 애니메이션을 Enum으로 알아오고, 다음 공격이 있다는 bool을 true로 변환, 그 결과를 bool로 return
	bool CheckAttackKey();
	int CalAtt(int _Value);	//현재 공격의 공격력 계산

	//Hit관련
	Timer Hit_Timer_;


	//쿨타임 관련
	std::map<std::string, Timer*> SkillCoolTime_;
public:
	std::map<std::string, Timer*> GetSkillCoolTimeList()
	{
		return SkillCoolTime_;
	}
private:
	Timer* CreateSkillCoolTime(std::string _Name, float Time_); //새로운 스킬쿨타임을 동적으로 생성한다.
	void InitSkillCoolTime(); //여러 스킬쿨타임들을 초기화 한다.
	void CoolTimeUpdate(float _DeltaTime); //스킬 쿨타임을 업데이트한다.

	//공격관련
	GameEngineCollision* AttackCol_;
	GameEngineCollision* BottomAttackCol_;
	int AttackCount_;
	void AttackEnd();

	//"일단" 공격 1회가 끝나면 IsAttack_End == true > 이후 ReadyNextAttack 분기에 따라
	bool  IsAttack_End_;
	bool IsReadyNextAttack_;
	PlayerAnimations NextAttackAni_;

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



	void IdleStart(const StateInfo _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo _Info);

	void MoveStart(const StateInfo _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo _Info);

	void JumpStart(const StateInfo _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo _Info);
	void JumpEnd(const StateInfo _Info);

	void AutoAttackStart(const StateInfo _Info);
	void AutoAttackUpdate(float _DeltaTime, const StateInfo _Info);
	void AutoAttackEnd(const StateInfo _Info);

	void UpperSlashStart(const StateInfo _Info);
	void UpperSlashUpdate(float _DeltaTime, const StateInfo _Info);
	void UpperSlashEnd(const StateInfo _Info);

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

		float4 SuperArmorPos;
		float4 SuperArmorScale;
		float SuperArmorMul;

		//공격력
		int UpperSlashAtt;
		int AutoAttackAtt;
	};
	DefaultValue Value_;
};

