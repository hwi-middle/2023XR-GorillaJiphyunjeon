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
		SoundSlider->SetMinValue(0.0f);
		SoundSlider->SetMaxValue(2.0f);
		// 초기 값을 설정
		SoundSlider->SetValue(1.0f);
		SoundSlider->OnValueChanged.AddDynamic(this, &UIGOptionSlide::SetMouseSensitivity);		
	}
}

void UIGOptionSlide::SetBGM(const float InValue)
{
	for(USoundCue* BGM: BGMSoundsData)
	{
		BGM->VolumeMultiplier = InValue;
		ValueText->SetText(FText::AsNumber(InValue * 100.0f));
	}
}

void UIGOptionSlide::SetSFX(const float InValue)
{
	for(USoundCue* SFX: SFXSoundsData)
	{
		SFX->VolumeMultiplier = InValue;
		ValueText->SetText(FText::AsNumber(InValue * 100.0f));
	}
}

void UIGOptionSlide::SetMouseSensitivity(const float InValue)
{
	if(PlayerController != nullptr)
	{		
		PlayerController->InputYawScale_DEPRECATED = InValue;
		PlayerController->InputPitchScale_DEPRECATED = InValue;
		ValueText->SetText(FText::AsNumber(InValue));
	}
}

void UIGOptionSlide::NativeConstruct()
{
	Super::NativeConstruct();
	SoundSlider = Cast<USlider>(GetWidgetFromName(TEXT("Slider")));
	ValueText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Value")));
	

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
	if (SoundSlider)
	{
		// 슬라이더의 범위를 설정 (예: 0.0부터 1.0까지)
		SoundSlider->SetMinValue(0.0f);
		SoundSlider->SetMaxValue(1.0f);
		// 초기 값을 설정
		SoundSlider->SetValue(0.5f);		
	}
}
