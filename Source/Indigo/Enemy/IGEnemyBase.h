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
	UPROPERTY(VisibleAnywhere)
	uint32 MaxHp;
	
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
};
