// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "IGCrystalSlot.generated.h"

class UButton;
class AIGPlayerCharacter;
class AIGCrystalBase;
class UImage;

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
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> CrystalSlot1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> CrystalSlot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> CrystalSlot3;

private:
	TObjectPtr<AIGPlayerCharacter> Character;

	int32 CrystalFragCount;
	
};
