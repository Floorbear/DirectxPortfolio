#pragma once
#include <GameEngineCore/GameEngineActor.h>


//렌더러를 가지는 액터들은 이 클래스를 상속 받는다.
//스프라이트 리소스를 좀 더 활용하기 용이하게 하기위한 클래스
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

	AttackData CurAttackData_;

protected:

	GameEngineTextureRenderer* MainRenderer_;
	GameEngineTextureRenderer* ShadowRenderer_;

	//shadow관련 함수& 변수
	void CreateDNFAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeDNFAnimation(const std::string& _Name);
	void ShadowUpdate();

	float4 ShadowPos_;
	float4 ShadowRot_;

	float4 PrevPos_;


	GameEngineCollision* BotCol_;
	float4 BotPos_;
	
	//픽셀충돌 관련 함수
	//이동량(미래에 이동할 양)을 매게변수로
	bool CanMove(const float4& _MoveValue);
	//세팅이 안된것을 체크 해 주는 함수
	void ErrorCheck();

	//Update에서 호출
	//하는 역할
	//1. 에러 체크
	//2. Shadow업데이트
	void DNFUpdate();

	//start에서 호출
	//하는 역할
	//1. MainRenderer 생성
	virtual void DNFStart();


	//Update에서 돌려줘야함
	void ZSort();

	bool IsStart_; //DnfStart 호출했냐
	
	//체공 관련
	bool OnAir_; //Jump중?
	float GroundYPos_;

	//경직도
	float Stiffness_;




private:

};

