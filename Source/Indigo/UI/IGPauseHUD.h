// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGPauseHUD.generated.h"

class UIGOptionWidget;
class UIGExitButton;
class UButton;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGPauseHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGPauseHUD(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OpenOption();
	
	UFUNCTION()
	void OpenMainTitle();
	
	UFUNCTION()
	void ClosePause();

	UFUNCTION()
	void OpenPause();
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<UIGOptionWidget> OptionWidget;

	UPROPERTY()
	TObjectPtr<UButton> ContinueButton;
	
	UPROPERTY()
	TObjectPtr<UButton> OptionButton;
	
	UPROPERTY()
	TObjectPtr<UButton> MainTitleButton;

private:
	UPROPERTY()
	TObjectPtr<APlayerController> Controller;
	
};
