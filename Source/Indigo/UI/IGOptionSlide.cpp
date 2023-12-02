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
#include "Components/ProgressBar.h"
#include "Sound/SoundCue.h"
#include "Indigo/Util/IGSaveOption.h"

UIGOptionSlide::UIGOptionSlide(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

}

void UIGOptionSlide::SetSliderType(const ESliderType InType)
{
	SoundSlider->SetMinValue(0.01f);
	SoundSlider->SetMaxValue(2.0f);

	TObjectPtr<UIGSaveOption> OptionSaveData = Cast<UIGSaveOption>(UGameplayStatics::LoadGameFromSlot(TEXT("Option"), 0));
	if(OptionSaveData == nullptr)
	{
		OptionSaveData = Cast<UIGSaveOption>(UGameplayStatics::CreateSaveGameObject(UIGSaveOption::StaticClass()));
		OptionSaveData->SFXSound = 1;
		OptionSaveData->BGMSound = 1;
		OptionSaveData->MouseSensivity = 1;
		SoundSlider->SetValue(1.0f);
		UGameplayStatics::SaveGameToSlot(OptionSaveData, TEXT("Option"), 0);		
	}
	
	SoundSlider->OnMouseCaptureBegin.AddDynamic(this, &UIGOptionSlide::PlayClickSound);
	switch (InType)
	{
		case ESliderType::BGM:
			SetBGM(OptionSaveData->BGMSound);
			SoundSlider->SetValue(OptionSaveData->BGMSound);
			SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetBGM);
			break;
		case ESliderType::SFX:
			SetSFX(OptionSaveData->SFXSound);
			SoundSlider->SetValue(OptionSaveData->SFXSound);
			SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetSFX);	
			break;
		case ESliderType::MouseSensitivity:
			SetMouseSensitivity(OptionSaveData->MouseSensivity);
			SoundSlider->SetValue(OptionSaveData->MouseSensivity);
			SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetMouseSensitivity);	
			break;
		default:
			
			break;
	}
}

void UIGOptionSlide::SetBGM(const float InValue)
{
	ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue * 50)));
	for(USoundCue* BGM: BGMSoundsData)
	{
		BGM->VolumeMultiplier = InValue;
		BGMSoundData = InValue;
	}
		ProgressBar->SetPercent(InValue/2);
}

void UIGOptionSlide::SetSFX(const float InValue)
{
	ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue  * 50)));
	for(USoundCue* SFX: SFXSoundsData)
	{
		SFX->VolumeMultiplier = InValue;
		SFXSoundData = InValue;
	}
		ProgressBar->SetPercent(InValue/2);
}

void UIGOptionSlide::SetMouseSensitivity(const float InValue)
{
	if(PlayerDataAsset != nullptr)
	{
		PlayerDataAsset->MouseYawScale = InValue;
		PlayerDataAsset->MousePitchScale = InValue;
		MouseData = InValue;
		
		ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue  * 50)));
		ProgressBar->SetPercent(InValue/2);
	}
}

void UIGOptionSlide::NativeConstruct()
{
	Super::NativeConstruct();
	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
	PlayerDataAsset = LoadObject<UIGPlayerDataAsset>(nullptr, TEXT("/Script/Indigo.IGPlayerDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_PlayerData.DA_PlayerData'"), nullptr, LOAD_None, nullptr, nullptr);
	SoundSlider = Cast<USlider>(GetWidgetFromName(TEXT("Slider")));
	ValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Value")));
	ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Percent")));
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
