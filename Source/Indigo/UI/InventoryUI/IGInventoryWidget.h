// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGInventoryWidget.generated.h"

class UIGInventory;

UCLASS()
class INDIGO_API UIGInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TObjectPtr<UIGInventory> Inventory;

};
