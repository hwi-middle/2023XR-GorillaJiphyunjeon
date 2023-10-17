// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/Character/IGEnemyBase.h"
#include "IGTutorialJangseung.generated.h"

class AIGGate;
class AIGTutorialJangseungPlace;

UCLASS()
class INDIGO_API AIGTutorialEnemyJangseung : public AIGEnemyBase
{
	GENERATED_BODY()
public:
	AIGTutorialEnemyJangseung();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION()
	void OpenGate();
	
private:
	TObjectPtr<UStaticMeshComponent> Mesh;
	int32 DamageCount;
	APawn* PlayerCharacter;
	AIGTutorialJangseungPlace* JangseungPlace;
	
};
