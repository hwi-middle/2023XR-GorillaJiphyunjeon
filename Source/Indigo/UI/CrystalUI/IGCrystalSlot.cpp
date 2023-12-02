// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/CrystalUI/IGCrystalSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
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

	UMaterial* CustomCircelProgressBar = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/_GorillaJiphyunjeon/Material/UI/M_CrystalCooltime.M_CrystalCooltime'"));
	UMaterialInstanceDynamic* CircleProgressMaterial = UMaterialInstanceDynamic::Create(CustomCircelProgressBar, nullptr);

	CrystalSlot[0] = Cast<UImage>(GetWidgetFromName(TEXT("Rock")));	
	CrystalSlot[1] = Cast<UImage>(GetWidgetFromName(TEXT("Wave")));
	CrystalSlot[2] = Cast<UImage>(GetWidgetFromName(TEXT("Tree")));
	CooltimeProgress = Cast<UImage>(GetWidgetFromName(TEXT("Cooltime")));
	CrystalCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));
	CrystalFragCount = 0;
	DMI_CoolTime = CooltimeProgress->GetDynamicMaterial();
}

void UIGCrystalSlot::AddCrystal(AIGCrystalBase* InCrystal)
{
	if(CrystalFragCount > 3 || CrystalType != InCrystal->GetCrystalType())
	{
		return;
	}
	
	
	if(Cast<AIGMountainCrystal>(InCrystal) != nullptr)
	{
		CrystalFragCount++;
		CrystalCount->SetText(FText::AsNumber(1));
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[0]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
		}
	}
	else if(Cast<AIGWaveCrystal>(InCrystal) != nullptr)
	{
		CrystalFragCount++;
		CrystalCount->SetText(FText::AsNumber(3));
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[1]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
		}
	}	
	else if(Cast<AIGTreeCrystal>(InCrystal) != nullptr)
	{
		CrystalFragCount++;
		CrystalCount->SetText(FText::AsNumber(2));
		if(CrystalFragCount >= 3)
		{
			CrystalSlot[2]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
		}
	}
}
		

void UIGCrystalSlot::ActiveCrystal(int32 InNumber)
{
	
}

void UIGCrystalSlot::CrystalCooltime(const float InDurationTime)
{
	DMI_CoolTime->SetScalarParameterValue(FName("Param"), InDurationTime);
}

void UIGCrystalSlot::SetCrystalType(const ECrystal InCrystalType)
{
	CrystalType = InCrystalType;
	
	switch (InCrystalType)
	{
	case ECrystal::Mountain:
		CrystalSlot[0]->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f));
		CrystalSlot[1]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
		CrystalSlot[2]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));

		CrystalCount->SetText(FText::AsNumber(1));
		break;
	case ECrystal::Wave:
		CrystalSlot[0]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
		CrystalSlot[1]->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f));
		CrystalSlot[2]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));

		CrystalCount->SetText(FText::AsNumber(3));
		break;
	case ECrystal::Tree:
		CrystalSlot[0]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
        CrystalSlot[1]->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
        CrystalSlot[2]->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f));

		CrystalCount->SetText(FText::AsNumber(2));
		break;

		default:
			break;
	}
}


