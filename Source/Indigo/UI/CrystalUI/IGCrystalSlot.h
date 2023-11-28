// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "IGCrystalSlot.generated.h"

class UButton;
class AIGPlayerCharacter;
class AIGCrystalBase;
class UImage;
class UTextBlock;
enum class ECrystal : uint32;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGCrystalSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGCrystalSlot(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void AddCrystal(AIGCrystalBase* InCrystal);
	UFUNCTION(BlueprintCallable)
	void ActiveCrystal(int32 InNumber);
	UFUNCTION(BlueprintCallable)
	void CrystalCooltime(const float InDurationTime);
	UFUNCTION(BlueprintCallable)
	void SetCrystalType(const ECrystal InCrystalType);
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> CrystalSlot[3];
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> CooltimeProgress;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> CrystalCount;

private:
	UPROPERTY()
	TObjectPtr<AIGPlayerCharacter> Character;

	UPROPERTY()
	int32 CrystalFragCount;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DMI_CoolTime;

	ECrystal CrystalType;
};
