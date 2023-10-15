// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Indigo/PhasePlace/IGPhasePlaceBase.h"
#include "IGBossGatePlace.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API AIGBossGatePlace : public AIGPhasePlaceBase
{
	GENERATED_BODY()
public:
	AIGBossGatePlace();

	FORCEINLINE void SetIsOpen(const bool InIsOpen){ bIsOpen = InIsOpen;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnterPhasePlace() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	uint8 bIsOpen : 1;
	
};
