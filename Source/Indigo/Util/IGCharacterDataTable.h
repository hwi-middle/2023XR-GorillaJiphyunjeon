// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	float HPValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float DefenseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float StaminaValue;
};
