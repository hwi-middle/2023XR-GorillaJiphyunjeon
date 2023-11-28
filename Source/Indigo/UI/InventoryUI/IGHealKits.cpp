// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/InventoryUI/IGHealKits.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UIGHealKits::UIGHealKits(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UIGHealKits::NativeConstruct()
{
	Super::NativeConstruct();

	HealKitSlot = Cast<UImage>(GetWidgetFromName(TEXT("HealKit")));
	HealKitEmpty = Cast<UImage>(GetWidgetFromName(TEXT("HealKitIcon")));
	HealKitCount= Cast<UTextBlock>(GetWidgetFromName(TEXT("HealKitCountText")));

	HealKitSlot->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
}

void UIGHealKits::SetHealKitCount(const int32 InValue)
{
	if(InValue == 0)
	{
		HealKitSlot->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		HealKitSlot->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	HealKitCount->SetText(FText::AsNumber(InValue)); 
}


