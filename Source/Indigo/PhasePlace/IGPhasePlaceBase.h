// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGPhasePlaceBase.generated.h"

class UBoxComponent;
class AIGPlayerCharacter;

UCLASS()
class INDIGO_API AIGPhasePlaceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGPhasePlaceBase();
	~AIGPhasePlaceBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnterPhasePlace();
	
	UPROPERTY()
	TObjectPtr<AIGPlayerCharacter> PlayerCharacter;

	uint8 bIsInCollision : 1;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxCollider;


};
