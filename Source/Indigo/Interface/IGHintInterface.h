// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGHintInterface.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UIGHintInterface : public UInterface
{
	GENERATED_BODY()

};

class INDIGO_API IIGHintInterface
{
	GENERATED_BODY()
public:
	//단서 이름
	virtual FString GetHintName() const = 0;

	//단서 내용
	virtual FString GetHintScript() const = 0;
};
