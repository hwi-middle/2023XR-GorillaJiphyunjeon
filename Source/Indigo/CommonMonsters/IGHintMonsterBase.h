// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "Indigo/Interactable/IGHintBase.h"
#include "IGHintMonsterBase.generated.h"

class AIGProvisoWispPlace;


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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE	void SetHintType(const EHintType InHintType) {HintType = InHintType;}
	
private:
	AIGProvisoWispPlace* WispPlace;
	
	UPROPERTY(EditAnywhere)
	EHintType HintType;

	float RespawnTime;
};
