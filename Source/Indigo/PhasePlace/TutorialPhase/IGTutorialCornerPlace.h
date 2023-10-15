// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/PhasePlace/IGPhasePlaceBase.h"
#include "IGTutorialCornerPlace.generated.h"

UCLASS()
class INDIGO_API AIGTutorialCornerPlace : public AIGPhasePlaceBase
{
	GENERATED_BODY()

public:
	AIGTutorialCornerPlace();
	~AIGTutorialCornerPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnterPhasePlace() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	
};
