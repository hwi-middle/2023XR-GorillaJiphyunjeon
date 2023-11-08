// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/CrystalUI/IGCrystalSlot.h"
#include "Components/Image.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/Interactable/IGMountainCrystal.h"
#include "Indigo/Interactable/IGWaveCrystal.h"
#include "Indigo/Interactable/IGTreeCrystal.h"


UIGCrystalSlot::UIGCrystalSlot(const FObjectInitializer& ObjectInitializer)	:Super(ObjectInitializer)
{
}

void UIGCrystalSlot::NativeConstruct()
{
	Super::NativeConstruct();

	CrystalSlot[0] = Cast<UImage>(GetWidgetFromName(TEXT("Crystal1")));	
	CrystalSlot[1] = Cast<UImage>(GetWidgetFromName(TEXT("Crystal2")));
	CrystalSlot[2] = Cast<UImage>(GetWidgetFromName(TEXT("Crystal3")));

	CrystalSlot[0]->SetVisibility(ESlateVisibility::Hidden);
	CrystalSlot[1]->SetVisibility(ESlateVisibility::Hidden);
	CrystalSlot[2]->SetVisibility(ESlateVisibility::Hidden);
	
	CrystalFragCount = 0;
}

void UIGCrystalSlot::AddCrystal(AIGCrystalBase* InCrystal)
{
	if(CrystalFragCount > 3)
	{
		return;
	}
	
	if(Cast<AIGTreeCrystal>(InCrystal) != nullptr)
	{
		CrystalFragCount++;
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[1]->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if(Cast<AIGWaveCrystal>(InCrystal) != nullptr)
	{
		
		CrystalFragCount++;
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[2]->SetVisibility(ESlateVisibility::Visible);
		}
	}	
	else if(Cast<AIGMountainCrystal>(InCrystal) != nullptr)
	{		
		CrystalFragCount++;
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[0]->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
		

void UIGCrystalSlot::ActiveCrystal(int32 InNumber)
{
	
}


