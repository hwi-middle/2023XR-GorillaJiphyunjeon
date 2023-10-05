// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indigo/Enemy/IGEnemyBase.h"
#include "IGHintMonsterBase.generated.h"

class AIGHintBase;

UCLASS()
class INDIGO_API AIGHintMonsterBase : public AIGEnemyBase
{
	
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AIGHintMonsterBase();
	AIGHintMonsterBase(const FString InSectorName);
	
	virtual void DropHint(); 
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	FString SectorName;
	TObjectPtr<UStaticMeshComponent> Mesh;
};
