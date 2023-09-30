// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGScriptDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FIGScriptDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString Script;


};
