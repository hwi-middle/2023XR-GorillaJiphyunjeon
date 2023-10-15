// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/PhasePlace/IGPhasePlaceBase.h"
#include "IGProvisoPhasePlace.generated.h"

UCLASS()
class INDIGO_API AIGProvisoPhasePlace : public AIGPhasePlaceBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGProvisoPhasePlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnterPhasePlace() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
