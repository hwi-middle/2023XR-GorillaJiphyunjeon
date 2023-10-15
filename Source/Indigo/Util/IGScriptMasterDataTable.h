// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IGScriptMasterDataTable.generated.h"


USTRUCT(Blueprintable)
struct INDIGO_API FIGScriptMasterDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	int32 ScriptMain;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	int32 ScriptSub;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	int32 ScriptDetail;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString ScriptCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString ScriptNext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString ScriptTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FString ScriptText;
};
