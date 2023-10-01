// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGIngameHUDWidget.generated.h"

class UIGGauge;
/**
 * 
 */
UCLASS()
class INDIGO_API UIGIngameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitHpGauge(float InMaxValue, float InInitialValue) const;
	void InitStaminaGauge(float InMaxValue, float InInitialValue) const;
	void InitSunMoonGauge(float InMaxValue, float InInitialValue) const;
	
	void UpdateHpGauge(float InValue) const;
	void UpdateStaminaGauge(float InValue) const;
	void UpdateSunMoonGauge(float InValue) const;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<UIGGauge> HpGauge;

	UPROPERTY()
	TObjectPtr<UIGGauge> StaminaGauge;
	
	UPROPERTY()
	TObjectPtr<UIGGauge> SunMoonGauge;
};
