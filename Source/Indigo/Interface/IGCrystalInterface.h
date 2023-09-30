// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IGCrystalInterface.generated.h"

UINTERFACE(MinimalAPI)
class UIGCrystalInterface: public UInterface
{
	GENERATED_BODY()
};

class INDIGO_API IIGCrystalInterface
{
	GENERATED_BODY()
public:
	virtual void TakeCrystal() = 0;
	virtual bool IsGetCrystal() const = 0;
	virtual FString GetCrystalName() const = 0;
};