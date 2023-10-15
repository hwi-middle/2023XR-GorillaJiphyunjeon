// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/PhasePlace/IGPhasePlaceBase.h"
#include "IGTutorialPhasePlace.generated.h"

UCLASS()
class INDIGO_API AIGTutorialPhasePlace : public AIGPhasePlaceBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGTutorialPhasePlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnterPhasePlace() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
