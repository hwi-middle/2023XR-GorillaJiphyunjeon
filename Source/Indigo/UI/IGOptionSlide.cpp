// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/IGOptionSlide.h"
#include "Components/Slider.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UObject/UnrealTypePrivate.h"
#include "Components/TextBlock.h"

UIGOptionSlide::UIGOptionSlide(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SoundDataAsset = FIGConstructorHelper::FindAndGetObject<UIGSoundDataAsset>(TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"));

}

void UIGOptionSlide::SetSliderType(const ESliderType InType)
{
	SoundSlider->SetMinValue(0.0f);
	SoundSlider->SetMaxValue(2.0f);
	SoundSlider->SetValue(1.0f);
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
	if(PlayerController != nullptr)
	{		
		PlayerController->InputYawScale_DEPRECATED = InValue;
		PlayerController->InputPitchScale_DEPRECATED = InValue;
		ValueText->SetText(FText::AsNumber(FMath::TruncToInt(InValue  * 50)));
	}
}

void UIGOptionSlide::NativeConstruct()
{
	Super::NativeConstruct();
	SoundSlider = Cast<USlider>(GetWidgetFromName(TEXT("Slider")));
	ValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Value")));
	ValueText->SetText(FText::AsNumber(50));

	if (SoundDataAsset)
	{
		for (TFieldIterator<UProperty> It(SoundDataAsset->GetClass()); It; ++It)
		{
			UProperty* Property = *It;
			USoundCue* SoundCue = Cast<USoundCue>(Property);
			if (SoundCue != nullptr)
			{
				FString Name = SoundCue->GetName();
				TArray<FString> NameArray;
				Name.ParseIntoArray(NameArray, TEXT("_"));

				if(NameArray[0] == TEXT("BGM"))
				{
					BGMSoundsData.Add(SoundCue);
				}
				else if(NameArray[0] == TEXT("SFX"))
				{
					SFXSoundsData.Add(SoundCue);
				}				
			}
		}
	}
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
