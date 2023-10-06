// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGSoundDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Indigo/Util/IGConstructorHelper.h"
#include "Sound/SoundCue.h"

UIGSoundDataAsset::UIGSoundDataAsset()
{
	CurrentSoundCue = nullptr;
}

void UIGSoundDataAsset::PlayCurrentSound() const
{
	UGameplayStatics::PlaySound2D(this, CurrentSoundCue, 1.0f);
}

void UIGSoundDataAsset::PlaySound(const UObject* InWorldContextObject, const TCHAR* InSoundCueKey) const
{
	if (SoundCueMap.Contains(InSoundCueKey))
	{
		const TObjectPtr<USoundCue> TempSoundCue = Cast<USoundCue>(SoundCueMap[InSoundCueKey]);
		UGameplayStatics::PlaySound2D(InWorldContextObject, TempSoundCue);	
	}	
}

void UIGSoundDataAsset::AddSoundCueBySoundCue(const TCHAR* InSoundCueKey, USoundCue* InSoundCue)
{
	SoundCueMap.Add(InSoundCueKey, InSoundCue);

	CurrentSoundCue = InSoundCue;		
}

void UIGSoundDataAsset::InitSoundCueByPath(const TCHAR* InSoundCueKey, const TCHAR* InPath)
{
	const TObjectPtr<USoundCue> TempSoundCue = LoadObject<USoundCue>(nullptr, InPath, nullptr, LOAD_None, nullptr, nullptr);	
	
	SoundCueMap.Add(InSoundCueKey, TempSoundCue);
	CurrentSoundCue = TempSoundCue;
}

void UIGSoundDataAsset::SetCurrentSoundCue(const TCHAR* InSoundCueKey)
{
	if (SoundCueMap.Contains(InSoundCueKey))
	{
		CurrentSoundCue = Cast<USoundCue>(SoundCueMap[InSoundCueKey]);
	}	
}
