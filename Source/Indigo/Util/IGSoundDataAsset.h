// Copyright GorillaJiphyunjeon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IGSoundDataAsset.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class INDIGO_API UIGSoundDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UIGSoundDataAsset();

	//현재 사운드 재생
	void PlayCurrentSound() const;
	//검색해서 재생
	void PlaySound(const UObject* InWorldContextObject,const TCHAR* InSoundCueKey) const;
	
	//사운드큐 데이터로 사운드큐 맵 추가
	void AddSoundCueBySoundCue(const TCHAR* InSoundCueKey, USoundCue* InSoundCue);
	//경로로 사운드큐 맵 추가
	void InitSoundCueByPath(const TCHAR* InSoundCueKey, const TCHAR* InPath);
	//현재 사운드 변경
	void SetCurrentSoundCue(const TCHAR* InSoundCueKey);	
	
	FORCEINLINE USoundCue* GetCurrentSoundCue() const {return CurrentSoundCue;}
	
private:
	UPROPERTY()
	TObjectPtr<USoundCue> CurrentSoundCue;

	UPROPERTY()
	TMap<FString, USoundCue*> SoundCueMap;
	
};
