// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGTextMasterDataTable.generated.h"


USTRUCT(Blueprintable)
struct INDIGO_API FIGTextMasterDataTable: public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FString TextCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FString Text;
	
	
};
