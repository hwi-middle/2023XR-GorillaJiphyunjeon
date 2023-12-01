// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Indigo/Interface/IGCharacterStatus.h"
#include "IGPlayerCharacter.generated.h"

class UIGPlayerWeaponAnimInstance;
class APostProcessVolume;
class UIGPlayerDataAsset;
class UIGPlayerControlDataAsset;
enum class ECrystal : uint32;
class UIGIngameHUDWidget;
class UIGTutotialWidget;
class UIGGIFTutorialWidget;
class UIGPauseHUD;
class UIGPlayerAnimInstance;
class UIGCharacterDataParser;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UIGPlayerInventory;
class UIGSoundDataAsset;
class UIGShinmyophil;
class UQuest;
class UAnimMontage;
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
	ExhaustedPhase1 = 0x20,
	// 탈진 (일월 게이지 비활성화)
	ExhaustedPhase2 = 0x40,
	// 탈진 (일월 게이지 획득량 감소)
	CrystalActivated = 0x80,
	CrystalCooldown = 0x100,
	Dead = 0x200,
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

	UPROPERTY()
	uint8 bIsHudDisabled : 1;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGIngameHUDWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGIngameHUDWidget> HudWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGTutotialWidget> TutorialWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGTutotialWidget> TutorialWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGGIFTutorialWidget> GIFTutorialWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGGIFTutorialWidget> GIFTutorialWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIGPauseHUD> PauseWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UIGPauseHUD> PauseWidget;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	//신묘필 대사 갱신
	void UpdateShinmyophilScript(const FString InText);

	//체력템 획득
	void AddHealKit();

	//BGM 변경
	void SetVillageBGM();
	void SetBossBGM();

	//Puause 위젯 띄우기
	void ShowPause();
	
	//GIF튜토리얼 위젯 띄우기
	void ShowFirstHealKitGIFTutorial();
	void ShowFirstCrystalGIFTutorial();
	void ShowFirstBossGIFTutorial();
	
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
	TObjectPtr<UInputAction> Crystal1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crystal2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Crystal3Action;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShowTutorialWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseHealKit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Pause;

	// 애니메이션
	UPROPERTY()
	TObjectPtr<UIGPlayerAnimInstance> PlayerAnimInstance;

	// UPROPERTY()
	// TObjectPtr<UIGPlayerWeaponAnimInstance> WeaponAnimInstance;
	
	// UPROPERTY()
	// TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	// 조준
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	uint8 bIsAimingHit : 1;

	UPROPERTY()
	FHitResult AimingHitResult;
	
	UPROPERTY()
	uint8 bIsAimingProperActor : 1;
	
	UPROPERTY()
	uint8 bIsFirstGetHealKit : 1;

	UPROPERTY()
	FVector AimingStartPoint;

	UPROPERTY()
	FVector AimingEndPoint;

	UPROPERTY()
	FVector AimingWorldDirection;

	UPROPERTY()
	float AimingOriginalYaw;

	UPROPERTY()
	float AimingTargetYaw;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioComponent;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SetIsIdling();
	void SetIsRunning(const FInputActionValue& Value);
	void Interact();
	void Attack();
	void GenerateProjectile();
	void RotateToAimingTarget();
	void ProcessComboCommand();
	void ComboActionBegin();
	void SetComboCheckTimer();
	int32 GetComboAnimationFrameCount() const;
	void ComboCheck();
	void ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded);
	virtual void NotifyComboActionEnd();
	void StartRolling();
	void FinishRolling();
	void EnableExhaustion();
	void OnHitProjectile();
	void ManageStaminaByTime(); // 초당 스태미나 소모/회복량 관리
	void ActivateCrystalByIndex(uint32 Index);
	void ManageCrystalActivationByTime();
	void ManageCrystalCooldownByTime();
	void ActivateCrystal1();
	void ActivateCrystal2();
	void ActivateCrystal3();
	void TutorialWidgetVisible();
	void UseHeal();
	void PlayDieSequence();
	void PlayFadeInSequence();

	//데미지 계산
	float ComputeDamage();



public:
	void PlayFadeOutSequence();
	void DisableHUD();
	void EnableHUD();

public:
	FORCEINLINE USpringArmComponent* GetCameraSpringArm() const { return CameraSpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UIGShinmyophil* GetShinmyophil() const { return Shinmyophil; }
	FORCEINLINE UIGPlayerInventory* GetInventory() const { return PlayerInventory; }
	FORCEINLINE EPlayerState GetCurrentState() const { return CurrentState; }
	FORCEINLINE int32 GetCurrentCombo() const { return CurrentCombo; }

private:
	// 플레이어 능력치
	FIGCharacterDataTable* CharacterDataTable;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UIGPlayerDataAsset> PlayerDataAsset;

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
	float StaminaConsumptionAmountOnNormalAttack;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountOnStrongAttack;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountOnRoll;

	UPROPERTY(VisibleAnywhere)
	float StaminaRecoveryAmountPerSecondOnIdle;

	UPROPERTY(VisibleAnywhere)
	float StaminaRecoveryAmountPerSecondOnWalk;

	UPROPERTY(VisibleAnywhere)
	float StaminaConsumptionAmountPerSecondOnRunning;

	// 3타 시스템에 필요한 정보
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAnimMontage> ComboActionMontage;
	
	UPROPERTY(VisibleAnywhere)
	int32 CurrentCombo = 0;
	
	UPROPERTY(VisibleAnywhere)
	FTimerHandle ComboTimerHandle;

	UPROPERTY(VisibleAnywhere)
	bool HasNextComboCommand = false;
	
	// 기타 필요한 정보
	UPROPERTY(VisibleAnywhere)
	float ExhaustionPhase1Duration;

	UPROPERTY(VisibleAnywhere)
	float ExhaustionPhase2Duration;

	UPROPERTY(VisibleAnywhere)
	float ElapsedCrystalActivationTime;

	UPROPERTY(VisibleAnywhere)
	float ElapsedCrystalCooldownTime;

	UPROPERTY(VisibleAnywhere)
	float RotateToAimingTargetDuration;
	
	UPROPERTY(VisibleAnywhere)
	float ElapsedRotateToAimingTargetTime;
	
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

	//BGM
	UPROPERTY()
	class USoundCue* CurrentBGM;

	//체력가능 횟수
	UPROPERTY()
	int32 HealCount;

	// 사운드
	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;

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
	void CheckCrystal_DEBUG();
};
