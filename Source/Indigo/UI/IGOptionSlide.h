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
class UProgressBar;
class UIGSaveOption;
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

	void SetSliderType(const ESliderType InType);

	UFUNCTION(BlueprintCallable)
	void SetBGM(const float InValue);
	UFUNCTION(BlueprintCallable)
	void SetSFX(const float InValue);
	UFUNCTION(BlueprintCallable)
	void SetMouseSensitivity(const float InValue);
	UFUNCTION(BlueprintCallable)
	void PlayClickSound();

	UFUNCTION(BlueprintCallable)
	float GetBgmSoundValue() const {return BGMSoundData;}
	UFUNCTION(BlueprintCallable)
	float GetSFXSoundValue() const {return SFXSoundData;}
	UFUNCTION(BlueprintCallable)
	float GetMouseSoundValue() const {return MouseData;}
	
	FORCEINLINE float GetValue() const {return SoundSlider->GetValue(); }
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USlider> SoundSlider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> ProgressBar;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BGMSoundData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SFXSoundData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MouseData;

};
