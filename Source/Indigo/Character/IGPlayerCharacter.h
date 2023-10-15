// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Indigo/Interface/IGCharacterStatus.h"
#include "IGPlayerCharacter.generated.h"

class APostProcessVolume;
class UIGPlayerDataAsset;
class UIGPlayerControlDataAsset;
enum class ECrystal : uint32;
class UIGIngameHUDWidget;
class UIGPlayerAnimInstance;
class UIGCharacterDataParser;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UIGPlayerInventory;
class UIGSoundDataAsset;
class UIGShinmyophil;
struct FInputActionValue;
struct FIGCharacterDataTable;

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPlayerState : uint32
{
	None = 0x00,
	Idling = 0x01,
	// 움직임이 없는 상태
	Walking = 0x02,
	// 걷는 중
	Running = 0x04,
	// 달리는 중
	Rolling = 0x08,
	// 구르는 중
	Attacking = 0x10,
	// 공격 중
	Enforced = 0x20,
	// 공격 강화 활성화
	ExhaustedPhase1 = 0x40,
	// 탈진 (일월 게이지 비활성화)
	ExhaustedPhase2 = 0x80,
	// 탈진 (일월 게이지 획득량 감소)
	CrystalActivated = 0x100,
	CrystalCooldown = 0x200,
	Dead = 0x400,
	All = 0xff,
};

ENUM_CLASS_FLAGS(EPlayerState);

UCLASS()
class INDIGO_API AIGPlayerCharacter : public ACharacter, public IIGCharacterStatus
{
	GENERATED_BODY()

public:
	AIGPlayerCharacter();

private:
	EPlayerState CurrentState;

	bool CheckPlayerState(const EPlayerState InState) const;
	void AddPlayerState(const EPlayerState InState);
	void RemovePlayerState(const EPlayerState InState);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGIngameHUDWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGIngameHUDWidget> HudWidget;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	//인터페이스 함수
	virtual FORCEINLINE float GetHp() const override { return Hp; }
	virtual FORCEINLINE void SetHp(const float InValue) override { Hp = InValue; }
	virtual FORCEINLINE float GetAttackValue() const override { return AttackValue; }
	virtual FORCEINLINE void SetAttackValue(const float InValue) override { AttackValue = InValue; }
	virtual FORCEINLINE float GetAttackRate() const override { return AttackRate; }
	virtual FORCEINLINE void SetAttackRate(const float InValue) override { AttackRate = InValue; }
	virtual FORCEINLINE float GetAttackRange() const override { return AttackRange; }
	virtual FORCEINLINE void SetAttackRange(const float InValue) override { AttackRange = InValue; }
	virtual FORCEINLINE float GetDefenceValue() const override { return DefenceValue; }
	virtual FORCEINLINE void SetDefenseValue(const float InValue) override { DefenceValue = InValue; }
	virtual FORCEINLINE float GetStaminaValue() const override { return StaminaValue; }
	virtual FORCEINLINE void SetStaminaValue(const float InValue) override { StaminaValue = InValue; }
	virtual FORCEINLINE bool IsDead() const override { return bIsDead; }

private:
	// 조작
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGPlayerControlDataAsset> PlayerControlDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ToggleSunMoonAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crystal1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crystal2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crystal3Action;

	// 애니메이션
	UPROPERTY()
	TObjectPtr<UIGPlayerAnimInstance> AnimInstance;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> BrushMesh;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SetIsIdling();
	void SetIsRunning(const FInputActionValue& Value);
	void Interact();
	void Attack();
	void FinishAttack();
	void StartRolling();
	void FinishRolling();
	void ToggleSunMoon();
	void ConsumeSunMoonByTime();
	void EnableExhaustion();
	void OnHitProjectile();
	void ManageStaminaByTime(); // 초당 스태미나 소모/회복량 관리
	void ActivateCrystalByIndex(uint32 Index);
	void ManageCrystalActivationByTime();
	void ManageCrystalCooldownByTime();
	void ActivateCrystal1();
	void ActivateCrystal2();
	void ActivateCrystal3();
	void PlayDieSequence();
	void PlayFadeInSequence();

	//데미지 계산
	float ComputeDamage();

public:
	void PlayFadeOutSequence();

public:
	FORCEINLINE USpringArmComponent* GetCameraSpringArm() const { return CameraSpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UIGShinmyophil* GetShinmyophil() const { return Shinmyophil; }
	FORCEINLINE EPlayerState GetCurrentState() const { return CurrentState; }

private:
	// 플레이어 능력치
	FIGCharacterDataTable* CharacterDataTable;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGPlayerDataAsset> PlayerDataAsset;

	UPROPERTY(VisibleAnywhere)
	float SunMoonValue;

	UPROPERTY(VisibleAnywhere)
	float Hp;

	UPROPERTY(VisibleAnywhere)
	float AttackValue;

	UPROPERTY(VisibleAnywhere)
	float AttackRate;

	UPROPERTY(VisibleAnywhere)
	float AttackRange;

	UPROPERTY(VisibleAnywhere)
	float DefenceValue;

	UPROPERTY(VisibleAnywhere)
	float StaminaValue;

	UPROPERTY(VisibleAnywhere)
	uint8 bIsDead : 1;

	UPROPERTY(VisibleAnywhere)
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere)
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere)
	float RollSpeed;

	UPROPERTY(VisibleAnywhere)
	int32 NormalAttackDamageMin;

	UPROPERTY(VisibleAnywhere)
	int32 NormalAttackDamageMax;

	UPROPERTY(VisibleAnywhere)
	int32 StrongAttackDamageMin;

	UPROPERTY(VisibleAnywhere)
	int32 StrongAttackDamageMax;

	// 증감값
	UPROPERTY(VisibleAnywhere)
	float SunMoonRecoveryAmountOnAttackHit;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountOnNormalAttack;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountOnStrongAttack;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountOnRoll;

	UPROPERTY(VisibleAnywhere)
	float SunMoonConsumptionAmountOnAttack;

	UPROPERTY(VisibleAnywhere)
	float StaminaRecoveryAmountPerSecondOnIdle;

	UPROPERTY(VisibleAnywhere)
	float StaminaRecoveryAmountPerSecondOnWalk;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountPerSecondOnRunning;

	UPROPERTY(VisibleAnywhere)
	float SunMoonAutoConsumptionAmount;

	// 기타 필요한 정보
	UPROPERTY(VisibleAnywhere)
	float SunMoonSection2Threshold;

	UPROPERTY(VisibleAnywhere)
	float SunMoonSection3Threshold;

	UPROPERTY(VisibleAnywhere)
	float SunMoonSection1DamageScaleFactor;

	UPROPERTY(VisibleAnywhere)
	float SunMoonSection2DamageScaleFactor;

	UPROPERTY(VisibleAnywhere)
	float SunMoonSection3DamageScaleFactor;

	UPROPERTY(VisibleAnywhere)
	float ExhaustionPhase1Duration;

	UPROPERTY(VisibleAnywhere)
	float ExhaustionPhase2Duration;

	UPROPERTY(VisibleAnywhere)
	float ElapsedSunMoonAutoConsumptionTime;

	UPROPERTY(VisibleAnywhere)
	float ElapsedCrystalActivationTime;

	UPROPERTY(VisibleAnywhere)
	float ElapsedCrystalCooldownTime;

	UPROPERTY(VisibleAnywhere)
	float SunMoonAutoConsumptionDelay;

	UPROPERTY(VisibleAnywhere)
	float DieZLocation;

	// 인벤토리
	UPROPERTY()
	TObjectPtr<UIGPlayerInventory> PlayerInventory;

	//신묘필
	UPROPERTY()
	TObjectPtr<UIGShinmyophil> Shinmyophil;
	
	UPROPERTY()
	ECrystal ActivatedCrystal;

	// 사운드
	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> TestSoundDataAsset;

	// 사망연출
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DMI_Grayscale;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DMI_Fade;

	UPROPERTY()
	float ElapsedDieSequenceTime;

	UPROPERTY()
	float ElapsedFadeSequenceTime;

private:
	// 디버그용
	UFUNCTION(Exec, Category="Command")
	void SetHp_DEBUG(const uint32 Value);

	UFUNCTION(Exec, Category="Command")
	void SetStaminaValue_DEBUG(const uint32 Value);

	UFUNCTION(Exec, Category="Command")
	void SetSunMoon_DEBUG(const uint32 Value);

	UFUNCTION(Exec, Category="Command")
	void CheckCrystal_DEBUG();
};
