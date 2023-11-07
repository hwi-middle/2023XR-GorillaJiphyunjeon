// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGHealKits.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGHealKits : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGHealKits(const FObjectInitializer& ObjectInitializer);

	void SetHealKitCount(const int32 InValue);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> HealKitSlot;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> HealKitCount;
};
