// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "IGHintMonsterBase.generated.h"

class AIGProvisoWispPlace;
class AIGWispAIController;
DECLARE_MULTICAST_DELEGATE(FOnFinishWispAttackDelegate)

enum class EHintType : uint8;

UCLASS()
class INDIGO_API AIGHintMonsterBase : public AIGEnemyBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AIGHintMonsterBase();
	
	virtual void DropHint(); 
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE float GetStoppingDistance() const { return StoppingDistance; }
	FORCEINLINE void SetIsFirstAttack(bool InIsFirstAttack){bIsFirstAttack = InIsFirstAttack;} 
	FORCEINLINE	bool GetIsDelay() const {return bIsDelay;}
	
	void PerformCloseAttack();
	void EndAttack();
	
	FOnFinishWispAttackDelegate OnFinishWispAttack;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE	void SetHintType(const EHintType InHintType) {HintType = InHintType;}
	
private:
	TObjectPtr<AIGProvisoWispPlace> WispPlace;
	
	UPROPERTY(EditAnywhere)
	EHintType HintType;

	UPROPERTY(EditAnywhere)
	float RespawnTime;

	UPROPERTY()
	float StoppingDistance;

	UPROPERTY()
	float AttackDelay;

	UPROPERTY()
	float ElapsedTime;
	
	UPROPERTY()
	float AttackTime;
	
	UPROPERTY()
	uint8 bIsDelay : 1;
	
	UPROPERTY()
	uint8 bIsAttack : 1;

	UPROPERTY()
	uint8 bIsFirstAttack : 1;

	UPROPERTY()
	FVector AttackStartLocation;
	
	UPROPERTY()
	FVector DashStartLocation;

	UPROPERTY()
	FVector DashEndLocation;

	UPROPERTY()
	float DashStartTime;

	UPROPERTY()
	float DashEndTime;
	
	UPROPERTY()
	uint8 bIsRetreating : 1;

	UPROPERTY()
	FVector RetreatStartLocation;

	UPROPERTY()
	FVector RetreatEndLocation;

	UPROPERTY()
	float RetreatStartTime;
	
	UPROPERTY()
	float RetreatEndTime;

};