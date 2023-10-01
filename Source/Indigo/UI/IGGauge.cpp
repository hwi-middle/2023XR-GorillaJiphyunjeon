// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGGauge.h"
#include "Components/ProgressBar.h"

UIGGauge::UIGGauge(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxValue = 100.f;
	CurrentValue = MaxValue;
}

void UIGGauge::NativeConstruct()
{
	Super::NativeConstruct();
}

void UIGGauge::Init(uint32 InMaxValue, uint32 InInitialValue)
{
	ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("GaugeBar")));
	MaxValue = InMaxValue;
	CurrentValue = InInitialValue;
	// check(ProgressBar);
	UpdateGaugeBar(CurrentValue);
}

void UIGGauge::UpdateGaugeBar(uint32 InValue)
{
	ensure(ProgressBar);
	CurrentValue = InValue;
	ProgressBar->SetPercent(CurrentValue / MaxValue);
}
