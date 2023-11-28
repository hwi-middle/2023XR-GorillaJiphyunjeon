// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/IGOptionSlide.h"
#include "Components/Slider.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Indigo/DataAsset/IGPlayerDataAsset.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UObject/UnrealTypePrivate.h"
#include "Components/TextBlock.h"
#include "Sound/SoundCue.h"

UIGOptionSlide::UIGOptionSlide(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

}

void UIGOptionSlide::SetSliderType(const ESliderType InType)
{
	SoundSlider->SetMinValue(0.01f);
	SoundSlider->SetMaxValue(2.0f);
	SoundSlider->SetValue(1.0f);

	SoundSlider->OnMouseCaptureBegin.AddDynamic(this, &UIGOptionSlide::PlayClickSound);
	if(InType == ESliderType::BGM)
	{
		SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetBGM);		
	}
	else if(InType == ESliderType::SFX)
	{
		SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetSFX);		
	}
	else if(InType == ESliderType::MouseSensitivity)
	{		
		SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetMouseSensitivity);		
	}
}

void UIGOptionSlide::SetBGM(const float InValue)
{
	ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue * 50)));
	for(USoundCue* BGM: BGMSoundsData)
	{
		BGM->VolumeMultiplier = InValue;
	}
}

void UIGOptionSlide::SetSFX(const float InValue)
{
	ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue  * 50)));
	for(USoundCue* SFX: SFXSoundsData)
	{
		SFX->VolumeMultiplier = InValue;
	}
}

void UIGOptionSlide::SetMouseSensitivity(const float InValue)
{
	if(PlayerDataAsset != nullptr)
	{
		PlayerDataAsset->MouseYawScale = InValue;
		PlayerDataAsset->MousePitchScale = InValue;
		
		ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue  * 50)));
	}
}

void UIGOptionSlide::NativeConstruct()
{
	Super::NativeConstruct();
	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
	PlayerDataAsset = LoadObject<UIGPlayerDataAsset>(nullptr, TEXT("/Script/Indigo.IGPlayerDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerData.DA_PlayerData'"), nullptr, LOAD_None, nullptr, nullptr);
	SoundSlider = Cast<USlider>(GetWidgetFromName(TEXT("Slider")));
	ValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Value")));
	ValueText->SetText(FText::AsNumber(50));
	PlayerDataAsset->MouseYawScale = 1.0f;
	PlayerDataAsset->MousePitchScale = 1.0f;

	if (SoundDataAsset)
	{
		for (TObjectIterator<USoundCue> It; It; ++It)
		{
			if (It->IsA(USoundCue::StaticClass()))
			{
				USoundCue* SoundCue = Cast<USoundCue>(*It);
				SoundCue->VolumeMultiplier = 1.0f;
				
				if (SoundCue != nullptr && SoundCue->GetName().StartsWith(TEXT("BGM")))
				{
					BGMSoundsData.Add(SoundCue);
				}
				else if (SoundCue != nullptr && SoundCue->GetName().StartsWith(TEXT("SFX")))
				{
					SFXSoundsData.Add(SoundCue);
				}
			}
		}
	}
}

void UIGOptionSlide::PlayClickSound()
{
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->UIClick);
}
