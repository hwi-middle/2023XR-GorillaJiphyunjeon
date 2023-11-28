// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGLevelButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Indigo/DataAsset/IGSoundDataAsset.h"
#include "Sound/SoundCue.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/PlayerStart.h"
#include "Indigo/Character/IGPlayerCharacter.h"
#include "UObject/UObjectGlobals.h"

void UIGLevelButton::NativeConstruct()
{
	Super::NativeConstruct();

	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/DA_SoundCueData.DA_SoundCueData'"), nullptr, LOAD_None, nullptr, nullptr);
	
	
	LevelButton = Cast<UButton>(GetWidgetFromName(TEXT("LevelMoveButton")));
	
	ButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonName")));

	LevelButton->OnClicked.AddDynamic(this, & UIGLevelButton::MoveLevel);
}

void UIGLevelButton::MoveLevel()
{
	LevelButton->OnClicked.Clear();
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->UIGameStart);

	
	AsyncLevelLoad(TEXT("/Game/_GorillaJiphyunjeon/Level/"), TEXT("64-WispTest"));	
}

void UIGLevelButton::OnTargetLevelLoaded()
{
	
}

void UIGLevelButton::AsyncLevelLoad(const FString LevelDir, const FString& LevelName)
{
	LoadPackageAsync(LevelDir + LevelName,
	FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
	{
		if(Result == EAsyncLoadingResult::Succeeded)
		{
			AsyncLevelLoadFinished(LevelName);
		}
	}
	),
	0,
	PKG_ContainsMap);
}

void UIGLevelButton::AsyncLevelLoadFinished(const FString LevelName)
{
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
}
