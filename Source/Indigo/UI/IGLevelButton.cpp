// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGLevelButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Indigo/Util/IGSoundDataAsset.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void UIGLevelButton::NativeConstruct()
{
	Super::NativeConstruct();
	SoundDataAsset = LoadObject<UIGSoundDataAsset>(nullptr, TEXT("/Script/Indigo.IGSoundDataAsset'/Game/_GorillaJiphyunjeon/DataAssets/SoundCueDataAsset.SoundCueDataAsset'"), nullptr, LOAD_None, nullptr, nullptr);
	LevelButton = Cast<UButton>(GetWidgetFromName(TEXT("LevelMoveButton")));
	
	ButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonName")));

	LevelButton->OnClicked.AddDynamic(this, &UIGLevelButton::MoveLevel);
	
}

void UIGLevelButton::MoveLevel()
{
	LevelButton->OnClicked.Clear();
	
	UGameplayStatics::PlaySound2D(this, SoundDataAsset->SystemGameStart);
	
	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
			UGameplayStatics::OpenLevel(this, TEXT("Test"));        
		}), SoundDataAsset->SystemGameStart->GetDuration(), false);	
}
