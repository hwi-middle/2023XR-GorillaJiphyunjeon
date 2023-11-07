// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGStraightProjectile.h"
#include "IGPlayerComboProjectile3.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class INDIGO_API AIGPlayerComboProjectile3 : public AIGStraightProjectile
{
	GENERATED_BODY()
public:
	AIGPlayerComboProjectile3();
	
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
};
