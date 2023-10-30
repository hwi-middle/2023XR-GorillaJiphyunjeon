// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Indigo/Interface/IGCharacterStatus.h"
#include "IGEnemyBase.generated.h"

UCLASS()
class INDIGO_API AIGEnemyBase : public ACharacter, public IIGCharacterStatus
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIGEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
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

	// Getter/Setter
	FORCEINLINE float GetDetectRange() const { return 3000.f; }
	FORCEINLINE FVector GetOrigin() const { return Origin; }

protected:
	UPROPERTY(VisibleAnywhere)
	float MaxHp;

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
	FVector Origin;
};
