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
		CrystalSlot[CrystalFragCount]->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f));	
		CrystalFragCount++;
	}
	else if(Cast<AIGWaveCrystal>(InCrystal) != nullptr)
	{
		CrystalSlot[CrystalFragCount]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 1.0f));
		CrystalFragCount++;
	}	
	else if(Cast<AIGMountainCrystal>(InCrystal) != nullptr)
	{
		CrystalSlot[CrystalFragCount]->SetColorAndOpacity(FLinearColor(0.6f, 0.3f, 0.0f));
		CrystalFragCount++;
	}
}
		

void UIGCrystalSlot::ActiveCrystal(int32 InNumber)
{
	
}


