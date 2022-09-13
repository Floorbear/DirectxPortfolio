#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "DNFMath.h"
#include "DNFGlobalValue.h"


//렌더러를 가지는 액터들은 이 클래스를 상속 받는다.
//스프라이트 리소스를 좀 더 활용하기 용이하게 하기위한 클래스
enum class AttackType
{
	Above,
	Below
};

struct AttackData
{
	int ZPos = 0; // ZPos == 0 > 공격이 Z축의 영향을 받지 않는다. 
	std::string AttackName = "";
	int AttCount = 0;
	int MaxAttCount = 10;
	AttackType Type = AttackType::Above;
	Effect AttEffect = Effect::None;
	int Att = 0;
	bool IsCritical = false;
	float Stiffness = 0.f; //경직
	float RStiffness =0.0f; //역경직
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

	//_Dir의 X값으로 Flip
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
	//픽셀충돌 관련 함수
	//이동량(미래에 이동할 양)을 매게변수로
	bool CanMove(const float4& _MoveValue);

	//세팅이 안된것을 체크 해 주는 함수
	void ErrorCheck();

	//Update에서 호출
	void DNFUpdate();

	//start에서 호출
	virtual void DNFStart();

	//Update에서 돌려줘야함
	void ZSort();

	virtual void HPBarUpdate(){}; //(지금당장은) 이 클래스를 상속받은 몬스터의 HPBarUpdate를 위한 함수

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* ShadowRenderer_;
	std::list< GameEngineTextureRenderer**> AllDNFRenderer_;

	//shadow관련 함수& 변수
	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeDNFAnimation(const std::string& _Name);
	void ResetDNFAnimation();
	void ShadowUpdate();

	float4 ShadowPos_;
	float4 ShadowRot_;

	float4 PrevPos_;
	float4 BotPos_;
	GameEngineCollision* BotCol_;


	bool IsStart_; //DnfStart 호출했냐

	//Fsm관련
	GameEngineStateManager StateManager_;

	//힘,중력 관련
	Force Force_;
	
	//체공 관련
	bool OnAir_; //Jump중?
	float AirborneTime_;
	float GroundYPos_;

	//경직 관련
	float Stiffness_;
	void GiveAndRecevieStiffness(AttackData& _Data, DNFRenderObject* _Other); //피격자가 호출, 경직과 역경직관리
	void StiffnessUpdate(float& _DeltaTime); 	//경직 업데이트, Update문에서 최우선적으로 호출

	//무적 관련
	Timer GodTime_;


	//체력관련
	int MaxHP_;	//최대 체력
	int CurHP_;	//현재 체력
	void CalHP(int _Value); //_Value값 만큼 체력을 더하거나 뺀다.



	//Hit관련
	AttackData PrevHitData_; //내가 방금 Hit한 Attack의 정보
	GameEngineCollision* HitAbove_;
	GameEngineCollision* HitBelow_;
	float4 DamageFontMovePos_;
	void SetDamageFont(int _Value, float4 _WorldPos, bool IsCritical);
	void HitColCheck(ColOrder _Order); //호출자 Monster면 _Oter에는 PlayerAttack이 들어감
	bool HitCheck(AttackType _Type, DNFRenderObject* _Other);//파라미터 : 확인할 공격 타입
	bool AboveHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);
	bool BelowHitCheck(GameEngineCollision* _this, GameEngineCollision* _Other);
	bool IsZPosHit(int _ZPos);

	//슈퍼아머 관련
	bool IsSuperArmor_;
	Timer SuperArmorTimer_;

	//이펙트 관련
	EffectActor* SetEffect(Effect _Effect, float4 _Pos, float4 _Dir = float4::ZERO);
	float4 HitEffectMovePos_;

private:

};

