// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "IGHintMonsterBase.generated.h"

class AIGProvisoWispPlace;
class AIGWispAIController;
class UIGWispAnimInstance;
DECLARE_MULTICAST_DELEGATE(FOnFinishWispAttackDelegate)

enum class ECrystal : uint32;
UCLASS()
class INDIGO_API AIGHintMonsterBase : public AIGEnemyBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AIGHintMonsterBase();
	
	virtual void DropCrystal(); 
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }
	FORCEINLINE	bool GetIsDelay() const {return bIsDelay;}

	FORCEINLINE	bool GetIsHit() const {return bIsHit;}
	FORCEINLINE	void IsHitFinish() { bIsHit = false;}
	FORCEINLINE	ECrystal GetCrystalType() const { return CrystalType;}

	//공격
	void PerformCloseAttack();

	void PerformMountainAttack();
	void PerformWaveAttack();
	void PerformTreeAttack();

	void EndAttack();
	
	FOnFinishWispAttackDelegate OnFinishWispAttack;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE	void SetCrystalType(const ECrystal InCrystalType) {CrystalType = InCrystalType;}
	
private:
	UPROPERTY()
	TObjectPtr<UIGWispAnimInstance> AnimInstance;

	UPROPERTY()
	TObjectPtr<AActor> PlayerActor;
	
	UPROPERTY(EditAnywhere)
	ECrystal CrystalType;

	UPROPERTY(EditAnywhere)
	float RespawnTime;

	UPROPERTY()
	float StoppingDistance;
	
	UPROPERTY()
	float CloseAttackDistance;

	UPROPERTY()
	float AttackDelay;

	UPROPERTY()
	float ElapsedTime;
	
	UPROPERTY()
	float AttackTime;
	
	UPROPERTY()
	float AttackSpeed;
	
	UPROPERTY()
	float RetreatTime;
	
	UPROPERTY()
	uint8 bIsDelay : 1;
	
	UPROPERTY()
	uint8 bIsAttack : 1;
	
	UPROPERTY()
	uint8 bIsHit : 1;

	UPROPERTY()
	FVector AttackStartLocation;
	
	UPROPERTY()
	FVector DashStartLocation;

	UPROPERTY()
	FVector DashEndLocation;
	
	UPROPERTY()
	uint8 bIsRetreating : 1;

	UPROPERTY()
	FVector RetreatStartLocation;

	UPROPERTY()
	FVector RetreatEndLocation;
		
	FDelegateHandle DelegateHandle;
	
	UPROPERTY()
	FVector SpawnPos;
	
};