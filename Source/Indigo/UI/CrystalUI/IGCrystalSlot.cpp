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

	CrystalSlot1 = Cast<UImage>(GetWidgetFromName(TEXT("Crystal1")));	
	CrystalSlot2 = Cast<UImage>(GetWidgetFromName(TEXT("Crystal2")));
	CrystalSlot3 = Cast<UImage>(GetWidgetFromName(TEXT("Crystal3")));
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
		if(CrystalFragCount == 2)
		{
			CrystalSlot3->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f));			
		}
		else if(CrystalFragCount == 1)
		{
			CrystalSlot2->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f));			
		}
		else if(CrystalFragCount == 0)
		{
			CrystalSlot1->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f));			
		}
		CrystalFragCount++;
	}
	else if(Cast<AIGWaveCrystal>(InCrystal) != nullptr)
	{
		if(CrystalFragCount == 2)
		{
			CrystalSlot3->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 1.0f));			
		}
		if(CrystalFragCount == 1)
		{
			CrystalSlot2->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 1.0f));			
		}
		if(CrystalFragCount == 0)
		{
			CrystalSlot1->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 1.0f));			
		}
		CrystalFragCount++;
	}	
	else if(Cast<AIGMountainCrystal>(InCrystal) != nullptr)
	{
		if(CrystalFragCount == 2)
		{			
			CrystalSlot3->SetColorAndOpacity(FLinearColor(0.6f, 0.3f, 0.0f));
		}
		if(CrystalFragCount == 1)
		{			
			CrystalSlot2->SetColorAndOpacity(FLinearColor(0.6f, 0.3f, 0.0f));
		}
		if(CrystalFragCount == 0)
		{
			CrystalSlot1->SetColorAndOpacity(FLinearColor(0.6f, 0.3f, 0.0f));		
		}
		CrystalFragCount++;
	}
}
		

void UIGCrystalSlot::ActiveCrystal(int32 InNumber)
{
	
}


