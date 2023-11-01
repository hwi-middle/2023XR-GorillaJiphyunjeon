// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IGOptionWidget.generated.h"

class UIGOptionSlide;
class UButton;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class INDIGO_API UIGOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGOptionWidget(const FObjectInitializer& ObjectInitializer);

	void CloseOption();

	void OpenCredit();
	void OpenSliderOption();
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<UIGOptionSlide> BGM;

	UPROPERTY()
	TObjectPtr<UIGOptionSlide> SFX;

	UPROPERTY()
	TObjectPtr<UIGOptionSlide> Mouse;
	
	UPROPERTY()
	TObjectPtr<UButton> OptionCloseButton;

	UPROPERTY()
	TObjectPtr<UButton> CreditButton;
	
	UPROPERTY()
	TObjectPtr<UButton> SliderOptionButton;
	
	UPROPERTY()
	TObjectPtr<UButton> SaveButton;
	
	UPROPERTY()
	TObjectPtr<UCanvasPanel> CreditPanel;
	
	UPROPERTY()
	TObjectPtr<UCanvasPanel> OptionPanel;
	
	
};
