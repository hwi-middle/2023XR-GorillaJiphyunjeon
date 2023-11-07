// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IGPlayerWeaponAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGPlayerWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint8 bIsPlayerRunning : 1;

public:
	void SetIsPlayerRunning(const bool InValue) { bIsPlayerRunning = InValue; }
};
