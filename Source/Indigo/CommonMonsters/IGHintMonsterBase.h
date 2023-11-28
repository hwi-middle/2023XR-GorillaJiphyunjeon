// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Animation/IGWispAnimInstance.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "IGHintMonsterBase.generated.h"

class AIGProvisoWispPlace;
class AIGWispAIController;
class UIGWispAnimInstance;
class UIGSoundDataAsset;
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
	FORCEINLINE float GetExplosionDistance() const { return ExplosionDistance; }
	FORCEINLINE	bool GetIsDelay() const {return bIsDelay;}

	FORCEINLINE	bool GetIsHit() const {return bIsHit;}
	FORCEINLINE	void IsHitFinish() { bIsHit = false;}
	FORCEINLINE	bool GetIsExplosion() const { return  AnimInstance->GetIsExplosion();}

	
	void PerformCloseAttack();
	void PerformBombAttack();
	void Explosion();
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
	
	UPROPERTY(EditAnywhere)
	ECrystal CrystalType;

	UPROPERTY(EditAnywhere)
	float RespawnTime;

	UPROPERTY()
	float StoppingDistance;
	
	UPROPERTY()
	float ExplosionDistance;

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

	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;
	
};