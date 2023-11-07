// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGStraightProjectile.h"
#include "IGPlayerComboProjectile1.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class INDIGO_API AIGPlayerComboProjectile1 : public AIGStraightProjectile
{
	GENERATED_BODY()
public:
	AIGPlayerComboProjectile1();
	
private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComp; 
};
