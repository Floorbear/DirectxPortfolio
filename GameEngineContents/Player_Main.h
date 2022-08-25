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

	//�� ����ī��Ʈ << ���Ͱ� ���� ������ ������ �´� ���� ����
	int GetAttackCount()
	{
		return AttackCount_;
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


	//����

	//���ݰ���
	GameEngineCollision* AttackCol_;
	GameEngineCollision* BottomAttackCol_;
	int AttackCount_;

	//"�ϴ�" ���� 1ȸ�� ������ IsAttack_End == true > ���� ReadyNextAttack �б⿡ ����
	bool  IsAttack_End_;
	bool IsReadyNextAttack_;
	PlayerAnimations NextAttackAni_;

	//UI
	GameEngineUIRenderer* UIRenderer_;


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



	//���� ���� ����Ű�� ���� ���� �ƹ�Ű�� ������ ������ float4::zero����
	float4 GetMoveDir();


	//Flip�� �Ȼ��³� �ƴϳ�
	bool IsDirXPositive();

	bool IsPressMoveKey();

	//Force����
	Force Force_;

	//FSM
	GameEngineStateManager StateManager_;

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

	//DefaultValues
	void InitDefaultValue();
	struct DefaultValue
	{
		float4 AutoAttackPos;
		float4 AutoAttackScale;
		float4 UpperSlashPos;
		float4 UpeerSlashScale;
	};
	DefaultValue Value_;
};

