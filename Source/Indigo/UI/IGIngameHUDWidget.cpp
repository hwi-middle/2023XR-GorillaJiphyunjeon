// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGIngameHUDWidget.h"
#include "IGGauge.h"
#include "QuestUI/IGQuestList.h"
#include "Indigo/Inventory/IGShinmyophil.h"
#include "Indigo/UI/Shinmyophil/IGShinmyophilText.h"
#include "Indigo/UI/CrystalUI/IGCrystalSlot.h"
#include "Indigo/Interactable/IGCrystalBase.h"
#include "Indigo/UI/InventoryUI/IGHealKits.h"
#include "Indigo/Interactable/IGMountainCrystal.h"
#include "Indigo/Interactable/IGTreeCrystal.h"
#include "Indigo/Interactable/IGWaveCrystal.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Indigo/Character/IGEnemyBase.h"

void UIGIngameHUDWidget::InitHpGauge(float InMaxValue, float InInitialValue) const
{
	HpGauge->Init(InMaxValue, InInitialValue);
}

void UIGIngameHUDWidget::InitStaminaGauge(float InMaxValue, float InInitialValue) const
{
	StaminaGauge->Init(InMaxValue, InInitialValue);
}

void UIGIngameHUDWidget::InitQuestList(UQuest* InQuest) const
{
	ShinmyophilQuestList->InitQuest(InQuest);
}

void UIGIngameHUDWidget::UpdateHpGauge(const float InValue) const
{
	HpGauge->UpdateGaugeBar(InValue);
}

void UIGIngameHUDWidget::UpdateStaminaGauge(const float InValue) const
{
	StaminaGauge->UpdateGaugeBar(InValue);
}

void UIGIngameHUDWidget::UpdateCrystalDebug(const FString& Str) const
{
	CrystalTextBlock->SetText(FText::FromString(Str));	
}

void UIGIngameHUDWidget::UpdateShinmyophilText(const FString& Str) const
{
	ShinmyophilText->SetText(Str);
}

void UIGIngameHUDWidget::AddCrystal(AIGCrystalBase* InCrystal) const
{
	if(Cast<AIGTreeCrystal>(InCrystal) != nullptr)
	{
		TreeCrystalSlot->AddCrystal(InCrystal);
	}
	else if(Cast<AIGWaveCrystal>(InCrystal) != nullptr)
	{
		WaveCrystalSlot->AddCrystal(InCrystal);
	}	
	else if(Cast<AIGMountainCrystal>(InCrystal) != nullptr)
	{
		MountainCrystalSlot->AddCrystal(InCrystal);
	}
}

void UIGIngameHUDWidget::SetHealKit(const int32 InValue) const
{
	HealKit->SetHealKitCount(InValue);
}

void UIGIngameHUDWidget::AimToEnemy(AActor* InActor)
{
	AIGEnemyBase* Enemy = Cast<AIGEnemyBase>(InActor);
	if(Enemy != nullptr)
	{
		AimImage->SetColorAndOpacity(FLinearColor(1.0, 0.0f, 0.0f));
	}
	else
	{
		AimImage->SetColorAndOpacity(FLinearColor(1.0, 1.0f, 1.0f));		
	}
	
}

void UIGIngameHUDWidget::AimToWhite()
{
	AimImage->SetColorAndOpacity(FLinearColor(1.0, 1.0f, 1.0f));
}

void UIGIngameHUDWidget::MountainCrystalCooltime(const float InDuraiontime)
{
	MountainCrystalSlot->CrystalCooltime(InDuraiontime);
}

void UIGIngameHUDWidget::WaveCrystalCooltime(const float InDuraiontime)
{
	WaveCrystalSlot->CrystalCooltime(InDuraiontime);
}

void UIGIngameHUDWidget::TreeCrystalCooltime(const float InDuraiontime)
{
	TreeCrystalSlot->CrystalCooltime(InDuraiontime);
}

void UIGIngameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpGauge = Cast<UIGGauge>(GetWidgetFromName(TEXT("HpGaugeBar")));
	StaminaGauge = Cast<UIGGauge>(GetWidgetFromName(TEXT("StaminaGaugeBar")));
	CrystalTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("CrystalDebug")));
	ShinmyophilQuestList = Cast<UIGQuestList>(GetWidgetFromName(TEXT("Quest_List")));
	ShinmyophilText = Cast<UIGShinmyophilText>(GetWidgetFromName(TEXT("IGShinmyophilText")));
	MountainCrystalSlot = Cast<UIGCrystalSlot>(GetWidgetFromName(TEXT("MountainCrystalSlots")));
	TreeCrystalSlot = Cast<UIGCrystalSlot>(GetWidgetFromName(TEXT("TreeCrystalSlots")));
	WaveCrystalSlot = Cast<UIGCrystalSlot>(GetWidgetFromName(TEXT("WaveCrystalSlots")));
	HealKit = Cast<UIGHealKits>(GetWidgetFromName(TEXT("HealKitSlot")));
	AimImage = Cast<UImage>(GetWidgetFromName(TEXT("Aim")));

	if(TreeCrystalSlot || WaveCrystalSlot || MountainCrystalSlot)
	{
		MountainCrystalSlot->SetCrystalType(ECrystal::Mountain);
		WaveCrystalSlot->SetCrystalType(ECrystal::Wave);
		TreeCrystalSlot->SetCrystalType(ECrystal::Tree);		
	}
}
