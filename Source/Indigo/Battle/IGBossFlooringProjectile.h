// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGStraightProjectile.h"
#include "IGBossFlooringProjectile.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class INDIGO_API AIGBossFlooringProjectile : public AIGStraightProjectile
{
	GENERATED_BODY()
public:
	AIGBossFlooringProjectile();

private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
};
