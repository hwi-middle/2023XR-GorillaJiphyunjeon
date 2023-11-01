// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "IGOptionSlide.generated.h"

class USlider;
class USoundCue;
class UIGSoundDataAsset;
class UTextBlock;
enum class ESliderType : int8
{
	SFX,
	BGM,
	MouseSensitivity
};


/**
 * 
 */
UCLASS()
class INDIGO_API UIGOptionSlide : public UUserWidget
{
	GENERATED_BODY()
public:
	UIGOptionSlide(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetSliderType(const ESliderType InType);
	
	void SetBGM(const float InValue);
	void SetSFX(const float InValue);
	void SetMouseSensitivity(const float InValue);

	FORCEINLINE float GetValue() const {return SoundSlider->GetValue(); }
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USlider> SoundSlider;

	ESliderType SliderType;

private:
	UPROPERTY()
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;

	UPROPERTY()
	TArray<USoundCue*> SFXSoundsData;

	UPROPERTY()
	TArray<USoundCue*> BGMSoundsData;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY()
	TObjectPtr<UTextBlock> ValueText;
};
