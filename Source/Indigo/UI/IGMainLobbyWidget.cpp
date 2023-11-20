// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "IGMainLobbyWidget.h"
#include "IGLevelButton.h"
#include "IGExitButton.h"
#include "IGOptionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UIGMainLobbyWidget::UIGMainLobbyWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{}

void UIGMainLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UIGLevelButton>(GetWidgetFromName(TEXT("GameStartButton")));
	OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("Option")));
	ExitButton = Cast<UIGExitButton>(GetWidgetFromName(TEXT("Exit")));
	OptionWidget = Cast<UIGOptionWidget>(GetWidgetFromName(TEXT("WBP_OptionWidget")));

	OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionButton->OnClicked.AddDynamic(this, &UIGMainLobbyWidget::OpenCloseOptionWidget);

	// 테스트
	TEST_GrayBoxButton = CastChecked<UButton>(GetWidgetFromName(TEXT("TEST_GrayBox")));
	TEST_GrayBoxButton->OnClicked.AddDynamic(this, &UIGMainLobbyWidget::OpenGrayBoxTestLevel);
	TEST_BossButton = CastChecked<UButton>(GetWidgetFromName(TEXT("TEST_Boss")));
	TEST_BossButton->OnClicked.AddDynamic(this, &UIGMainLobbyWidget::OpenBossTestLevel);
	TEST_WispButton = CastChecked<UButton>(GetWidgetFromName(TEXT("TEST_Wisp")));
	TEST_WispButton->OnClicked.AddDynamic(this, &UIGMainLobbyWidget::OpenWispTestLevel);
}

void UIGMainLobbyWidget::OpenCloseOptionWidget()
{
	if (OptionWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if (OptionWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UIGMainLobbyWidget::OpenGrayBoxTestLevel()
{
	UGameplayStatics::OpenLevel(this, "AD_GrayBox");
}

void UIGMainLobbyWidget::OpenBossTestLevel()
{
	UGameplayStatics::OpenLevel(this, "Test");
}

void UIGMainLobbyWidget::OpenWispTestLevel()
{
	UGameplayStatics::OpenLevel(this, "64-WispTest");
}
