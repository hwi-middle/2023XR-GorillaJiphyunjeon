// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGStraightProjectile.h"
#include "IGStraightWaveProjectile.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class INDIGO_API AIGStraightWaveProjectile : public AIGStraightProjectile
{
	GENERATED_BODY()
	
public:
	AIGStraightWaveProjectile();
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
};
