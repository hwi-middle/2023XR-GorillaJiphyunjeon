// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "IGCharacterDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FIGCharacterDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 HPValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 AttackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 AttackRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 DefenceValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 StaminaValue;
};
