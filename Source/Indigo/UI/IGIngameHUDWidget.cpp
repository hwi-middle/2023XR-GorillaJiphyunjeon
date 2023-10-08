// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGIngameHUDWidget.h"
#include "IGGauge.h"
#include "Components/TextBlock.h"

void UIGIngameHUDWidget::InitHpGauge(float InMaxValue, float InInitialValue) const
{
	HpGauge->Init(InMaxValue, InInitialValue);
}

void UIGIngameHUDWidget::InitStaminaGauge(float InMaxValue, float InInitialValue) const
{
	StaminaGauge->Init(InMaxValue, InInitialValue);
}

void UIGIngameHUDWidget::InitSunMoonGauge(float InMaxValue, float InInitialValue) const
{
	SunMoonGauge->Init(InMaxValue, InInitialValue);
}

void UIGIngameHUDWidget::UpdateHpGauge(const float InValue) const
{
	HpGauge->UpdateGaugeBar(InValue);
}

void UIGIngameHUDWidget::UpdateStaminaGauge(const float InValue) const
{
	StaminaGauge->UpdateGaugeBar(InValue);
}

void UIGIngameHUDWidget::UpdateSunMoonGauge(const float InValue) const
{
	SunMoonGauge->UpdateGaugeBar(InValue);
}

void UIGIngameHUDWidget::UpdateCrystalDebug(const FString& Str) const
{
	CrystalTextBlock->SetText(FText::FromString(Str));	
}

void UIGIngameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpGauge = Cast<UIGGauge>(GetWidgetFromName(TEXT("HpGaugeBar")));
	StaminaGauge = Cast<UIGGauge>(GetWidgetFromName(TEXT("StaminaGaugeBar")));
	SunMoonGauge = Cast<UIGGauge>(GetWidgetFromName(TEXT("SunMoonGaugeBar")));
	CrystalTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("CrystalDebug")));
}
