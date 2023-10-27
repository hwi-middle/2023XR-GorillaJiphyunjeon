// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Shinmyophil/IGShinmyophilText.h"
#include "IGIngameHUDWidget.generated.h"

class AIGCrystalBase;
class UTextBlock;
class UIGGauge;
class UIGQuestList;
class UIGQuest;
class UQuest;
class UIGShinmyophilText;
class UIGCrystalSlot;

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
	void InitQuestList(UQuest* InQuest) const;
	
	void UpdateHpGauge(float InValue) const;
	void UpdateStaminaGauge(const float InValue) const;
	void UpdateCrystalDebug(const FString& Str) const;
	void UpdateShinmyophilText(const FString& Str) const;
	void AddCrystal(AIGCrystalBase* InCrystal) const;

	FORCEINLINE FString GetShinmyophilText() const { return ShinmyophilText->GetText();}

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<UIGGauge> HpGauge;

	UPROPERTY()
	TObjectPtr<UIGGauge> StaminaGauge;

	UPROPERTY()
	TObjectPtr<UTextBlock> CrystalTextBlock;

	UPROPERTY()
	TObjectPtr<UIGQuestList> ShinmyophilQuestList;
	
	UPROPERTY()
	TObjectPtr<UIGShinmyophilText> ShinmyophilText;

	UPROPERTY()
	TObjectPtr<UIGCrystalSlot> MountainCrystalSlot;
	
	UPROPERTY()
	TObjectPtr<UIGCrystalSlot> TreeCrystalSlot;
	
	UPROPERTY()
	TObjectPtr<UIGCrystalSlot> WaveCrystalSlot;
};
