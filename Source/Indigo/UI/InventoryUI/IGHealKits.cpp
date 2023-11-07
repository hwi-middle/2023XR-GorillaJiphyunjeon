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

	HealKitSlot= Cast<UImage>(GetWidgetFromName(TEXT("HealKitIcon")));
	HealKitCount= Cast<UTextBlock>(GetWidgetFromName(TEXT("HealKitCountText")));
	
}

void UIGHealKits::SetHealKitCount(const int32 InValue)
{
	HealKitCount->SetText(FText::AsNumber(InValue)); 
}


