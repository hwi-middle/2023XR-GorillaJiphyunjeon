// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGMountainSpike.h"
#include "IGWispMountainAttackStone.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class INDIGO_API AIGWispMountainAttackStone : public AIGMountainSpike
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIGWispMountainAttackStone();

private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 

};
