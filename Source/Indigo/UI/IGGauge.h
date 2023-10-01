// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGGauge.generated.h"

/**
 * 
 */
UCLASS()
class INDIGO_API UIGGauge : public UUserWidget
{
	GENERATED_BODY()

public:
	UIGGauge(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

public:
	void Init(uint32 InMaxValue, uint32 InInitialValue);
	void UpdateGaugeBar(uint32 InValue);
	
protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> ProgressBar;

	UPROPERTY()
	float CurrentValue;

	UPROPERTY()
	float MaxValue;
};
