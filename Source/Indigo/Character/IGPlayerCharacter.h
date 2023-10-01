// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Indigo/Interface/IGCharacterStatus.h"
#include "IGPlayerCharacter.generated.h"

class UIGIngameHUDWidget;
class UIGPlayerAnimInstance;
class UIGCharacterDataParser;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FIGCharacterDataTable;

UENUM(Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPlayerState : uint32
{
	None = 0x00,
	Idling = 0x01,
	Walking = 0x02,
	Running = 0x04,
	Jumping = 0x08,
	Rolling = 0x10,
	Attacking = 0x20,
	Enforced = 0x40,
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

public:
    //인터페이스 함수
    virtual FORCEINLINE uint32 GetHp() const override {return Hp;}
    virtual FORCEINLINE void SetHp(const uint32 InValue) override{Hp = InValue;}
    virtual FORCEINLINE uint32 GetAttackValue() const override {return AttackValue;}
    virtual FORCEINLINE void SetAttackValue(const uint32 InValue) override {AttackValue = InValue;}
    virtual FORCEINLINE uint32 GetAttackRate() const override {return AttackRate;}
    virtual FORCEINLINE void SetAttackRate(const uint32 InValue) override {AttackRate = InValue;}
    virtual FORCEINLINE uint32 GetAttackRange() const override {return AttackRange;}
    virtual FORCEINLINE void SetAttackRange(const uint32 InValue) override {AttackRange = InValue;}
    virtual FORCEINLINE uint32 GetDefenceValue() const override {return DefenceValue;}
    virtual FORCEINLINE void SetDefenseValue(const uint32 InValue) override {DefenceValue = InValue;}
    virtual FORCEINLINE uint32 GetStaminaValue() const override {return StaminaValue;}
    virtual FORCEINLINE void SetStaminaValue(const uint32 InValue) override {StaminaValue = InValue;}
    virtual FORCEINLINE bool IsDead() const override {return bIsDead;} 
    
private:
	// 조작
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

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
	
	// 애니메이션
	UPROPERTY()
	TObjectPtr<UIGPlayerAnimInstance> AnimInstance;

protected:
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

public:
    FORCEINLINE USpringArmComponent* GetCameraSpringArm() const { return CameraSpringArm; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
    //멤버 변수
    UPROPERTY(VisibleAnywhere)
    uint32 Hp;
	
    UPROPERTY(VisibleAnywhere)
    uint32 AttackValue;
	
    UPROPERTY(VisibleAnywhere)
    uint32 AttackRate;
	
    UPROPERTY(VisibleAnywhere)
    uint32 AttackRange;
	
    UPROPERTY(VisibleAnywhere)
    uint32 DefenceValue;
	
    UPROPERTY(VisibleAnywhere)
    uint32 StaminaValue;
	
    UPROPERTY(VisibleAnywhere)
    uint8 bIsDead : 1;

	UPROPERTY(VisibleAnywhere)
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere)
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere)
	uint32 NormalAttackStaminaCost;
	
	UPROPERTY(VisibleAnywhere)
	uint32 StrongAttackStaminaCost;
	
    FIGCharacterDataTable* CharacterDataTable;
    
};
