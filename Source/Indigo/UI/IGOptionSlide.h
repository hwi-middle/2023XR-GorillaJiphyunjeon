// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "IGOptionSlide.generated.h"

class USlider;
class USoundCue;
class UIGSoundDataAsset;
class UIGPlayerDataAsset;
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

	UFUNCTION(BlueprintCallable)
	void SetBGM(const float InValue);
	UFUNCTION(BlueprintCallable)
	void SetSFX(const float InValue);
	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(const float InValue);
	UFUNCTION(BlueprintCallable)
	void PlayClickSound();
	
	FORCEINLINE float GetValue() const {return SoundSlider->GetValue(); }
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USlider> SoundSlider;

	ESliderType SliderType;

private:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGSoundDataAsset> SoundDataAsset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UIGPlayerDataAsset> PlayerDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USoundCue*> SFXSoundsData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<USoundCue*> BGMSoundsData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> ValueText;
};
