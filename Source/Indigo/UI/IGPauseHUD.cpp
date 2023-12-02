// Copyright GorillaJiphyunjeon. All Rights Reserved.


#include "Indigo/UI/IGPauseHUD.h"
#include "Indigo/UI/IGOptionWidget.h"
#include "Kismet/GamePlaystatics.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UIGPauseHUD::UIGPauseHUD(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UIGPauseHUD::OpenOption()
{
	OptionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UIGPauseHUD::OpenMainTitle()
{
	UGameplayStatics::OpenLevel(this, TEXT("MainTitle"));
}

void UIGPauseHUD::ClosePause()
{
	SetVisibility(ESlateVisibility::Hidden);
	Controller->bShowMouseCursor = false;
	Controller->bEnableMouseOverEvents = false;
	Controller->bEnableClickEvents = false;
	Controller->SetInputMode(FInputModeGameOnly());
	OptionWidget->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(this, false);
}

void UIGPauseHUD::OpenPause()
{
	SetVisibility(ESlateVisibility::Visible);
	Controller->bShowMouseCursor = true;
	Controller->bEnableMouseOverEvents = true;
	Controller->bEnableClickEvents = true;
	Controller->SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGamePaused(this, true);
}

void UIGPauseHUD::NativeConstruct()
{
	Super::NativeConstruct();

	Controller = UGameplayStatics::GetPlayerController(GWorld, 0);
	
	OptionWidget = Cast<UIGOptionWidget>(GetWidgetFromName(TEXT("Option")));
	OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("ShowOption")));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("Continue")));
	MainTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("MainTitle")));

	OptionWidget->SetVisibility(ESlateVisibility::Hidden);	
	ContinueButton->OnClicked.AddDynamic(this, &UIGPauseHUD::ClosePause);
	OptionButton->OnClicked.AddDynamic(this, &UIGPauseHUD::OpenOption);
	MainTitleButton->OnClicked.AddDynamic(this, &UIGPauseHUD::OpenMainTitle);
	
}
