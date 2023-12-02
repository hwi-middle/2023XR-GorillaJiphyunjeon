// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/TutorialUI/IGGIFTutorialWidget.h"
#include "MediaPlayer.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaTexture.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "Kismet/GameplayStatics.h"

UIGGIFTutorialWidget::UIGGIFTutorialWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}
	
void UIGGIFTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = UGameplayStatics::GetPlayerController(GWorld, 0);

	GIFTutorialCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Canvas")));
	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("Confirm")));
	TutorialDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
	TutorialTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")));
	TutorialGIF = Cast<UImage>(GetWidgetFromName(TEXT("GIF")));

	TutorialGIFPlayer = LoadObject<UMediaPlayer>(nullptr, TEXT("/Script/MediaAssets.MediaPlayer'/Game/_GorillaJiphyunjeon/UI/Game/Tutorial/TutorialGIF/MP_Test_HealTuto.MP_Test_HealTuto'"));
	HealTutorialGIFSource = LoadObject<UMediaSource>(nullptr, TEXT("/Script/MediaAssets.FileMediaSource'/Game/_GorillaJiphyunjeon/UI/Game/Tutorial/TutorialGIF/Test_HealTuto_Resize.Test_HealTuto_Resize'"));

	//실시간으로 불러오면 너무 느려서 생성할때 한꺼번에 가져옴 근데 이래도 느림
	TutorialGIFPlayer->OpenSource(HealTutorialGIFSource);
	
	ConfirmButton->OnClicked.AddDynamic(this, &UIGGIFTutorialWidget::CloseGIFTutorialWidget);
	
}

void UIGGIFTutorialWidget::CloseGIFTutorialWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	Controller->bShowMouseCursor = false;
	Controller->bEnableMouseOverEvents = false;
	Controller->bEnableClickEvents = false;
	Controller->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGamePaused(GWorld, false);
}

void UIGGIFTutorialWidget::VisibleGIFTutorialWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	Controller->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GWorld, true);
}

void UIGGIFTutorialWidget::SetTitle(const FText InTitle)
{
	TutorialTitle->SetText(InTitle);
}

void UIGGIFTutorialWidget::SetDescription(const FText InDesctription)
{
	TutorialDescription->SetText(InDesctription);
}

void UIGGIFTutorialWidget::PreSetByFirstHealKit()
{
	TutorialTitle->SetText(FText::FromString(TEXT("혈기의 호리병")));
	TutorialDescription->SetText(FText::FromString(TEXT("도깨비불을 처치 시 확률에 따라 혈기의 호리병을 얻을 수 있습니다.\n 혈기의 호리병을 사용하면 체력이 일부 회복됩니다.\n 획득한 아이템은 R키를 눌러 사용할 수 있습니다.")));
}

void UIGGIFTutorialWidget::PreSetByFirstCrystal()
{
	TutorialTitle->SetText(FText::FromString(TEXT("곡옥 조각")));
	TutorialDescription->SetText(FText::FromString(TEXT("도깨비불을 처치 시 확률에 따라 곡옥 조각을 얻을 수 있습니다.\n 동일한 곡옥 조각을 3개 모으면 해당 곡옥을 사용할 수 있습니다.\n 곡옥을 사용하면 보스 몬스터의 공격을 무효화 시킬 수 있습니다.")));

}

void UIGGIFTutorialWidget::PreSetByFirstBoss()
{
	TutorialTitle->SetText(FText::FromString(TEXT("곡옥 활성화")));	
	TutorialDescription->SetText(FText::FromString(TEXT("1, 2, 3키를 눌러 각 순서에 맞는 곡옥을 활성화 시킬 수 있습니다.\n 곡옥이 활성화되는 동안 보스의 공격은 통하지 않습니다.\n 활성화 된 곡옥은 일정 시간이 지나면 해제됩니다.")));

}


