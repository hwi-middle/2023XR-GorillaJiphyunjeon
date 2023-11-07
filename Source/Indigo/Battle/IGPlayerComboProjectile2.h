// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGStraightProjectile.h"
#include "IGPlayerComboProjectile2.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class INDIGO_API AIGPlayerComboProjectile2 : public AIGStraightProjectile
{
	GENERATED_BODY()
public:
	AIGPlayerComboProjectile2();
	
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
};
